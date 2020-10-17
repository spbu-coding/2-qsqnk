cmake_minimum_required(VERSION 3.17)
project(HW_2 C ASM)

set(CMAKE_C_STANDARD 11)

add_executable(HW_2 main.c sort.c sort.s)