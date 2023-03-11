cmake_minimum_required(VERSION 3.21)
project(tema3SD C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(tema3SD
        functions.c
        tasks.c
        library.h
        main.c)