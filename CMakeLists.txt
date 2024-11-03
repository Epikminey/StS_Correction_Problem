cmake_minimum_required(VERSION 3.29)
project(StS_Correction_Problem)

set(CMAKE_CXX_STANDARD 26)

include_directories(include)

add_executable(StS_Correction_Problem
        src/DistanceLevenshtein.cpp
        src/Instance.cpp
        src/Solution.cpp
        src/Algorithme.cpp
        src/main.cpp
        include/Sequence.h
        src/Sequence.cpp
        include/Case.h
        src/Case.cpp
)

