cmake_minimum_required(VERSION 3.15)
project(p2pChat)

set(CMAKE_CXX_STANDARD 17)

add_executable(p2pChat main.cpp chatRX.cpp chatRX.h chatTX.cpp chatTX.h)

FIND_PACKAGE(curses REQUIRED)
