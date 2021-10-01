cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

include_directories(./include)
include_directories(./modules/date/include)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(HelloWorld)

add_executable(HelloWorld src/main.cpp include/utils.hpp src/logger.cpp)
