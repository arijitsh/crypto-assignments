cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

PROJECT(simon)

add_compile_options( -g)

add_executable(simon
    main.cpp
    simon.cpp)



