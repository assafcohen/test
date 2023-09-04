#include <cstring>
#include <iostream>
#include <asio.hpp>

using asio::ip::tcp;

int main(int, char*[]) noexcept
{
    constexpr std::size_t maxLength = 1024;
    try
    {
        asio::io_context ioContext;

        tcp::socket s(ioContext);
        tcp::resolver resolver(ioContext);
        asio::connect(s, resolver.resolve("127.0.0.1", "61434"));

        std::cout << "Enter message: ";
        char request[maxLength]{};
        std::cin.getline(request, maxLength-1);
        size_t requestLength = strnlen_s(request,maxLength);
        asio::write(s, asio::buffer(request, requestLength));
        char l = 0;
        asio::read(s, asio::buffer(&l, 1));
        char reply[maxLength];
        size_t replyLength = asio::read(s, asio::buffer(reply, l));
        std::cout << "Reply is: " << std::string_view(reply, replyLength) << "\n";
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}