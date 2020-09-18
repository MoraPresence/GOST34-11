cmake_minimum_required(VERSION 3.16)
project(GOST34_11 C)

set(CMAKE_C_STANDARD 11)

add_executable(GOST34_11 main.c stribog_data.h)