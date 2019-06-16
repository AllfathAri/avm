cmake_minimum_required(VERSION 3.14)
project(avm C)

set(CMAKE_C_STANDARD 11)

add_executable(avm main.c vm.c vm.h instructions.c instructions.h collections.c collections.h)