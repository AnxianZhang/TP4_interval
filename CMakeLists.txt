cmake_minimum_required(VERSION 3.29)
project(TP4_interval C)

set(CMAKE_C_STANDARD 11)

add_executable(main.c
        main.c
        Interval.h
        Interval.c
        Node.h
        Node.c
)