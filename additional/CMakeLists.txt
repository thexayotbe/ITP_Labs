cmake_minimum_required(VERSION 3.29)
project(additional C)

set(CMAKE_C_STANDARD 11)

add_executable(additional main.c
        lab/lab.c
)
