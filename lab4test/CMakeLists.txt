cmake_minimum_required(VERSION 3.27)
project(lab4test)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(lab4test
        CSV_parser.h
        main.cpp
        print_tuple.h)
