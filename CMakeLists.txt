cmake_minimum_required(VERSION 3.14)
project(avm)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

add_executable(avm main.c vm.c vm.h instructions.c instructions.h collections.c collections.h mpc.c mpc.h)

add_executable(avm_test catch.hpp vm.c vm.h instructions.c instructions.h collections.c collections.h vm_tests.cpp instructions_tests.cpp)