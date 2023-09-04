#include <iostream>
#include <memory>
#include <utility>
#include <asio.hpp>

using asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket) : mSocket(std::move(socket)) { }

    void start()
    {
        std::cout << "Session started" << std::endl;
        doRead();
    }

    ~Session()
    {
        std::cout << "Session destructed" << std::endl;
    }

private:
    void doRead()
    {
        mSocket.async_read_some(asio::buffer(mData, cMaxLength),
                                // completion token as lambda that gets called on each completed read
                                [this](std::error_code ec, std::size_t length)
                                {
                                    if (!ec)
                                    {
                                        const auto message = std::string(mData, length);
                                        auto count = std::count_if(message.begin(),
                                                                   message.end(),
                                                                   [](auto c)
                                                                   {
                                                                       return true;
                                                                   });
                                        doWrite(count);
                                    }
                                });
    }

    void doWrite(std::size_t length)
    {        
        asio::async_write(mSocket,
                          asio::buffer(mData, length),
                          // completion token as lambda that gets called on each completed write
                          [this,self = shared_from_this()](std::error_code ec, std::size_t)
                          {
                              if (!ec)
                              {
                                  doRead();
                              }
                          });
    }

    tcp::socket mSocket;
    static constexpr std::size_t cMaxLength = 1024;
    char mData[cMaxLength];
};

class Server
{
public:
    Server(asio::io_context& ioContext, std::uint16_t port) : mAcceptor(ioContext, tcp::endpoint(tcp::v4(), port))
    {        
        doAccept();
        std::cout << "Waiting for connections on port " << port <<std::endl;
    }

private:
    void doAccept()
    {
        mAcceptor.async_accept(
                // completion token as lambda that gets called on each accept
                [this](std::error_code ec, tcp::socket socket)
                {
                    if (!ec)
                    {
                        std::cout << "Connection accepted" << std::endl;
                        std::make_shared<Session>(std::move(socket))->start();
                    }

                    doAccept();
                });
    }

    tcp::acceptor mAcceptor;
};

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: server <port>\n";
        return 1;
    }

    asio::io_context ioContext(21);
    Server s(ioContext, std::stoul(argv[1]));
    ioContext.run();
    return 0;
}