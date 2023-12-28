cmake_minimum_required(VERSION 3.27)
project(hw10INI)

set(CMAKE_CXX_STANDARD 20)

add_executable(hw10INI main.cpp
        Document.cpp
        Document.h
        ini.h
        Section.cpp
        Section.h
        test.h
        test_ini.cpp)
