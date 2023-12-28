cmake_minimum_required(VERSION 3.22)
project(hw5_Modules0a)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")

add_executable(hw5_Modules0a main.cpp
        module1.cpp
        module3.cpp
        module2.cpp)
