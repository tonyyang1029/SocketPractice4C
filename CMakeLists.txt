cmake_minimum_required(VERSION 3.29)
# project(SocketPractice C)

set(CMAKE_C_STANDARD 11)

project(socketserver C)
add_executable(socketserver server.c)

project(socketclient C)
add_executable(socketclient client.c)

add_library(socket socket.c
        socket.h)

target_link_libraries(socketserver socket)
target_link_libraries(socketclient socket)
