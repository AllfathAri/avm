cmake_minimum_required(VERSION 3.14)
project(avm)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

add_executable(avm main.c
        vm.c vm.h
        instructions.c instructions.h
        assembler.c assembler.h
        collections.c collections.h
        lib/mpc.c lib/mpc.h)

add_executable(avm_test
        vm.c vm.h  vm_tests.cpp
        instructions.c instructions.h instructions_tests.cpp
        assembler.c assembler.h assembler_tests.cpp
        collections.c collections.h
        lib/mpc.c lib/mpc.h
        lib/catch.hpp)