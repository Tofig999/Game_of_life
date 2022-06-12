cmake_minimum_required(VERSION 3.22)
project(GameOfLife2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(GameOfLife2
        Exceptions.cpp
        Exceptions.h
        Main.cpp
        Table.cpp
        Table.h)
