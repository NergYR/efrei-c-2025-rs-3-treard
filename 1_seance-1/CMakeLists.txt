cmake_minimum_required(VERSION 3.29)
project(seance_1 C)

set(CMAKE_C_STANDARD 23)

add_executable(seance_1 main.c
        boucles.c
        boucles.h
        types.c
        types.h
        conditions.h
        conditions.c)
