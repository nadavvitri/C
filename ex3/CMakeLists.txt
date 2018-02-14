cmake_minimum_required(VERSION 3.8)
project(ex3)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES GenericDFS.c SudokuTree.c SudokuSolver.c tester.c)
add_executable(ex3 ${SOURCE_FILES})