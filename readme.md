Dear candidate,

Thank you for applying to work in Incredibuild.

This is coding test, it shouldn't take more than an hour or two.

This project builds 2 executables, client and a server.

Both use STL and [Asio](https://think-async.com/Asio/).

You can assume that asio usage is correct, but you are encouraged to use its documentation.

The client executable source code is added for ease of use while you take the test - PLEASE DO NOT CHANGE IT.
You are encouraged to build and run client, for reproducing potential issues.

Build instructions:

1. mkdir build
2. cd build
3. cmake

The client and server have a simple protocol:

1. Client sends a string up to 1024 characters.
2. Server receives the string
3. Calculate the count digits in the string.
4. And replies with a byte for length to send and the result calculated in step 3 as a string.
5. Client receives reply and outputs reply to console.

Server code in server.cpp is not complete, it should be fixed.
Also some of the working parts are bug prone or may be rewritten for efficiency.

Please change server code ONLY! in order for it to work according to protocol.
solution should be only the modified server.cpp file.

Good luck.
