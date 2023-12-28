cmake_minimum_required(VERSION 3.27)
project(hw4_PersonalBudget)

set(CMAKE_CXX_STANDARD 20)

add_executable(hw4_PersonalBudget main.cpp
        Date.h
        Date.cpp
        Budget.cpp)
