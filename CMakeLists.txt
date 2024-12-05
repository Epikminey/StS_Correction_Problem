cmake_minimum_required(VERSION 3.29)
project(StS_Correction_Problem)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

include_directories(include)



add_executable(StS_Correction_Problem
        src/Case.cpp
        src/Sequence.cpp
        src/Instance.cpp
        src/Solution.cpp
        src/Algorithme.cpp
        src/main.cpp
        include/Case.h
        include/Sequence.h
        include/Instance.h
        include/Solution.h
        include/Algorithme.h
        include/Test.h
        src/Test.cpp
)
