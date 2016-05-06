cmake_minimum_required(VERSION 3.2)
project(vaois_server_client_socket)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

message("A Message.")

set(SERVER_SOURCE_FILES
    server2.c)

set(CLIENT_SOURCE_FILES
    client2.c)

add_executable(vaois_server ${SERVER_SOURCE_FILES})
add_executable(vaois_client ${CLIENT_SOURCE_FILES})
