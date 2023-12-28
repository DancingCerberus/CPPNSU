cmake_minimum_required(VERSION 3.27)
project(lab3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab3
        configuration.cpp
        configuration.h
        converter.cpp
        converter.h
        main.cpp
        wav_file.cpp
        wav_file.h)
