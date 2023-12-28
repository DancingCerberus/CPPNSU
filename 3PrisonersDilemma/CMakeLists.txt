cmake_minimum_required(VERSION 3.26)
project(3PrisonersDilemma)

set(CMAKE_CXX_STANDARD 23)

add_executable(3PrisonersDilemma main.cpp
        BetrayerStategy.cpp
        AlwaysBetrayStrategy.h
        Strategy/IStrategy.h
        Strategy/Choice.h
        Strategy/CooperatorStrategy.cpp
        Strategy/CooperatorStrategy.h
        Strategy/RandomStrategy.cpp
        Strategy/RandomStrategy.h
        Strategy/StrategyFactory.cpp
        Strategy/StrategyFactory.h
        Strategy/StrategyEnum.h
        Competition/ICompetition.h
        Competition/DetailedCompetition.cpp
        Competition/DetailedCompetition.h
        Competition/FastCompetition.cpp
        Competition/FastCompetition.h
        Competition/TournamentCompetition.cpp
        Competition/TournamentCompetition.h
        Defaults.h
        Competition/CompetitionEnum.h
        Strategy/VengefulStrategy.cpp
        Strategy/VengefulStrategy.h
        Parsers.cpp
        Parsers.h)
