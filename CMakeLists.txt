cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

include_directories(./include)
include_directories(./modules/date/include)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(ServerClient)

add_executable(Server src/main.cpp include/utils.hpp src/logger.cpp src/mockserver.cpp src/client.cpp)

add_executable(Client src/main_client.cpp include/utils.hpp src/logger.cpp src/mockserver.cpp src/client.cpp)

