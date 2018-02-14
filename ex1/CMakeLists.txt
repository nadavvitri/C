cmake_minimum_required(VERSION 3.8)
project(ex1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra -Wall -Wvla -std=c99")
set(SOURCE_FILES ex1.c)
add_executable(ex1 ${SOURCE_FILES})