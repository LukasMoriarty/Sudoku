cmake_minimum_required(VERSION 4.2)
project(Sudoku C)

set(CMAKE_C_STANDARD 99)

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
add_executable(Sudoku ${SOURCES})
