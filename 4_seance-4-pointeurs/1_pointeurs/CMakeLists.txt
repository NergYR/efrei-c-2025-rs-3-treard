cmake_minimum_required(VERSION 3.29)
project(pointers C)

set(CMAKE_C_STANDARD 23)


set(SRCS
    main.c
)

SET(HEADER
    main.h
)

add_executable(pointers ${SRCS} ${HEADERS})