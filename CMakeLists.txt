cmake_minimum_required(VERSION 3.21)

set(target diod_printer)

project(${target})

file(GLOB_RECURSE sources 
    inc/*.h
    src/*.h
    src/*.c
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${target} ${sources})

target_include_directories(${target} PUBLIC inc/)
target_include_directories(${target} PRIVATE src/)
