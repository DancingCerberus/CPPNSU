cmake_minimum_required(VERSION 3.27)
project(hw6_SmsEmailNotifier)

set(CMAKE_CXX_STANDARD 20)

add_executable(hw6_SmsEmailNotifier main.cpp
        INotifier.h
        SmsNotifier.cpp
        SmsNotifier.h
        EmailNotifier.cpp
        EmailNotifier.h)
