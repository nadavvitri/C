cmake_minimum_required(VERSION 3.8)
project(ex2)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra -Wall -Wvla -std=c99")
set(SOURCE_FILES MyString.c)
add_executable(ex2 ${SOURCE_FILES})