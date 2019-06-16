//
// Created by allfathari on 6/16/19.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"

extern "C" {
#include "vm.h"
}

//TEST_CASE("Initilizaing VM") {
//    VM vm;
//    vm_init(&vm);
// TODO: VM init tests
//}

#define BS(...) __VA_ARGS__
#define PREPARE_VM(bs, len) VM vm; vm_init(&vm); u_int8_t p_arr[] = bs; vm.program = byte_vector_from(p_arr, len);

TEST_CASE("LOAD execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        PREPARE_VM(BS({0, i, 1, 244}), 4)
        vm_run_once(&vm);
        REQUIRE(vm.registers[i] == 500);
    }
}

TEST_CASE("ADD execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        for (u_int8_t j = 0; j < 32; ++j) {
            for (u_int8_t k = 0; k < 32; ++k) {
                PREPARE_VM(BS({1, i, j, k}), 4)
                vm.registers[i] = 10;
                vm.registers[j] = 5;
                vm_run_once(&vm);
                if (i != j)
                    REQUIRE(vm.registers[k] == 15);
                else
                    REQUIRE(vm.registers[k] == 10);
            }
        }
    }
}

TEST_CASE("SUB execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        for (u_int8_t j = 0; j < 32; ++j) {
            for (u_int8_t k = 0; k < 32; ++k) {
                PREPARE_VM(BS({2, i, j, k}), 4)
                vm.registers[i] = 10;
                vm.registers[j] = 5;
                vm_run_once(&vm);
                if (i != j)
                    REQUIRE(vm.registers[k] == 5);
                else
                    REQUIRE(vm.registers[k] == 0);
            }
        }
    }
}

TEST_CASE("MUL execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        for (u_int8_t j = 0; j < 32; ++j) {
            for (u_int8_t k = 0; k < 32; ++k) {
                PREPARE_VM(BS({3, i, j, k}), 4)
                vm.registers[i] = 10;
                vm.registers[j] = 5;
                vm_run_once(&vm);
                if (i != j)
                    REQUIRE(vm.registers[k] == 50);
                else
                    REQUIRE(vm.registers[k] == 25);
            }
        }
    }
}

TEST_CASE("DIV execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        for (u_int8_t j = 0; j < 32; ++j) {
            for (u_int8_t k = 0; k < 32; ++k) {
                PREPARE_VM(BS({4, i, j, k}), 4)
                vm.registers[i] = 10;
                vm.registers[j] = 3;
                vm_run_once(&vm);
                if (i != j) {
                    REQUIRE(vm.registers[k] == 3);
                    REQUIRE(vm.remainder == 1);
                } else {
                    REQUIRE(vm.registers[k] == 1);
                    REQUIRE(vm.remainder == 0);
                }
            }
        }
    }
}

TEST_CASE("HLT execution") {
    // TODO: Test Halt
}

TEST_CASE("JMP execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        PREPARE_VM(BS({6, i, 0, 0}), 4)
        vm.registers[i] = 4;
        vm_run_once(&vm);
        REQUIRE(vm.pc == 4);
    }
}

TEST_CASE("JMPF execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        PREPARE_VM(BS({7, i, 0, 0, 5, 0, 0, 0}), 8)
        vm.registers[i] = 2;
        vm_run_once(&vm);
        REQUIRE(vm.pc == 4);
    }
}

TEST_CASE("JMPB execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        PREPARE_VM(BS({0, 0, 0, 10, 8, i, 0, 0}), 8)
        vm.registers[i] = 6;
        vm_run_once(&vm);
        vm_run_once(&vm);
        REQUIRE(vm.pc == 0);
    }
}

TEST_CASE("EQ execution") {}

TEST_CASE("NEQ execution") {}

TEST_CASE("GTE execution") {}

TEST_CASE("LTE execution") {}

TEST_CASE("LT execution") {}

TEST_CASE("GT execution") {}

TEST_CASE("JMPE execution") {}

TEST_CASE("NOP execution") {}

TEST_CASE("ALOC execution") {}

TEST_CASE("INC execution") {}

TEST_CASE("DEC execution") {}

TEST_CASE("DJMPE execution") {}

TEST_CASE("PRTS execution") {}

TEST_CASE("LOADF64 execution") {}

TEST_CASE("ADDF64 execution") {}

TEST_CASE("SUBF64 execution") {}

TEST_CASE("MULF64 execution") {}

TEST_CASE("DIVF64 execution") {}

TEST_CASE("EQF64 execution") {}

TEST_CASE("NEQF64 execution") {}

TEST_CASE("GTF64 execution") {}

TEST_CASE("GTEF64 execution") {}

TEST_CASE("LTF64 execution") {}

TEST_CASE("LTEF64 execution") {}

TEST_CASE("SHL execution") {}

TEST_CASE("SHR execution") {}

TEST_CASE("AND execution") {}

TEST_CASE("OR execution") {}

TEST_CASE("XOR execution") {}

TEST_CASE("NOT execution") {}

TEST_CASE("LUI execution") {}

TEST_CASE("CLOOP execution") {}

TEST_CASE("LOOP execution") {}

TEST_CASE("LOADM execution") {}

TEST_CASE("SETM execution") {}

TEST_CASE("PUSH execution") {}

TEST_CASE("POP execution") {}

TEST_CASE("CALL execution") {}

TEST_CASE("RET execution") {}

TEST_CASE("IGL execution") {}

#undef PREPARE_VM
#undef BS