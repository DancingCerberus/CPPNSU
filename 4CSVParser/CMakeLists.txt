cmake_minimum_required(VERSION 3.27)
project(lab4)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(lab4
        CSV_parser.h
        main.cpp
        print_tuple.h)
