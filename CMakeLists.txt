cmake_minimum_required(VERSION 3.22)

#project name
project(asm8051)
SET( CMAKE_VERBOSE_MAKEFILE on )

add_subdirectory(tools)
add_subdirectory(asm_table)
add_subdirectory(src)

add_subdirectory(test)