cmake_minimum_required(VERSION 3.25)
project(0distinctCompilation)

set(CMAKE_CXX_STANDARD 17)

add_executable(0distinctCompilation module1.cpp module1.h module2.h module2.c++ main.c++ module3.h module3.c++)
