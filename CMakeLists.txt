cmake_minimum_required(VERSION 3.26)
project(candidate)

set(CMAKE_CXX_STANDARD 23)
include_directories(asio-1.28.0/include)
add_executable(candidate server.cpp)
add_executable(client client.cpp)
