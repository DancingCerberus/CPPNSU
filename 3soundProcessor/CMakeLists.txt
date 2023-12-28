cmake_minimum_required(VERSION 3.27)
project(3soundProcessor)

set(CMAKE_CXX_STANDARD 20)

add_executable(3soundProcessor main.cpp
        Audio.h
        Audio.cpp
        WavEncoder.h
        WavEncoder.cpp
        Application.h
        Application.cpp
        Command/MuteCommand.h
        Command/MuteCommand.cpp
        AppParameters.h
        Command/MixCommand.h
        Command/MixCommand.cpp
        Command/InsertCommand.h
        Command/InsertCommand.cpp
        Command/ICommand.h
        Command/InsertCommand.cpp
)