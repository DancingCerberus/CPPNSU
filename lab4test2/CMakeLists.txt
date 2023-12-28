cmake_minimum_required(VERSION 3.27)
project(lab4test2)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(lab4test2
        CSV_parser.h
        main.cpp
        print_tuple.h)
