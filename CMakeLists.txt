cmake_minimum_required(VERSION 3.16)
project(kursach)

set(CMAKE_CXX_STANDERD 17)

file(GLOB_RECURSE SOURCES
        src/*.h
        src/*.cpp
        src/*.hpp
        )
add_executable(kursash ${SOURCES})

