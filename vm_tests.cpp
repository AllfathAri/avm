//
// Created by allfathari on 6/16/19.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "lib/catch.hpp"

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
        vm_run_once(&vm);
        vm.registers[i] = 6;
        vm_run_once(&vm);
        REQUIRE(vm.pc == 0);
    }
}

TEST_CASE("EQ execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        for (u_int8_t j = 0; j < 32; ++j) {
            PREPARE_VM(BS({9, i, j, 0, 9, i, j, 0}), 8);
            vm.registers[i] = 10;
            vm.registers[j] = 10;
            vm_run_once(&vm);
            REQUIRE(vm.equal_flag);

            vm.registers[j] = 20;
            vm_run_once(&vm);
            if (i != j) {
                REQUIRE(!vm.equal_flag);
            } else {
                REQUIRE(vm.equal_flag);
            }
        }
    }
}

TEST_CASE("NEQ execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        for (u_int8_t j = 0; j < 32; ++j) {
            PREPARE_VM(BS({10, i, j, 0, 10, i, j, 0}), 8);
            vm.registers[i] = 10;
            vm.registers[j] = 20;
            vm_run_once(&vm);
            if (i != j) {
                REQUIRE(vm.equal_flag);
            } else {
                REQUIRE(!vm.equal_flag);
            }

            vm.registers[j] = 10;
            vm_run_once(&vm);
            REQUIRE(!vm.equal_flag);
        }
    }
}

TEST_CASE("GTE execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        for (u_int8_t j = 0; j < 32; ++j) {
            PREPARE_VM(BS({11, i, j, 0, 11, i, j, 0, 11, i, j, 0}), 12);
            vm.registers[i] = 20;
            vm.registers[j] = 10;
            vm_run_once(&vm);
            REQUIRE(vm.equal_flag);

            vm.registers[i] = 10;
            vm_run_once(&vm);
            REQUIRE(vm.equal_flag);

            vm.registers[i] = 5;
            vm_run_once(&vm);
            if (i != j) {
                REQUIRE(!vm.equal_flag);
            } else {
                REQUIRE(vm.equal_flag);
            }
        }
    }
}

TEST_CASE("LTE execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        for (u_int8_t j = 0; j < 32; ++j) {
            PREPARE_VM(BS({12, i, j, 0, 12, i, j, 0, 12, i, j, 0}), 12);
            vm.registers[i] = 20;
            vm.registers[j] = 10;
            vm_run_once(&vm);
            if (i != j) {
                REQUIRE(!vm.equal_flag);
            } else {
                REQUIRE(vm.equal_flag);
            }

            vm.registers[i] = 10;
            vm_run_once(&vm);
            REQUIRE(vm.equal_flag);

            vm.registers[i] = 5;
            vm_run_once(&vm);
            REQUIRE(vm.equal_flag);
        }
    }
}

TEST_CASE("LT execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        for (u_int8_t j = 0; j < 32; ++j) {
            PREPARE_VM(BS({13, i, j, 0, 13, i, j, 0, 13, i, j, 0}), 12);
            vm.registers[i] = 20;
            vm.registers[j] = 10;
            vm_run_once(&vm);
            REQUIRE(!vm.equal_flag);

            vm.registers[i] = 10;
            vm_run_once(&vm);
            REQUIRE(!vm.equal_flag);


            vm.registers[i] = 5;
            vm_run_once(&vm);
            if (i != j) {
                REQUIRE(vm.equal_flag);
            } else {
                REQUIRE(!vm.equal_flag);
            }
        }
    }
}

TEST_CASE("GT execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        for (u_int8_t j = 0; j < 32; ++j) {
            PREPARE_VM(BS({14, i, j, 0, 14, i, j, 0, 14, i, j, 0}), 12);
            vm.registers[i] = 20;
            vm.registers[j] = 10;
            vm_run_once(&vm);
            if (i != j) {
                REQUIRE(vm.equal_flag);
            } else {
                REQUIRE(!vm.equal_flag);
            }

            vm.registers[i] = 10;
            vm_run_once(&vm);
            REQUIRE(!vm.equal_flag);


            vm.registers[i] = 5;
            vm_run_once(&vm);
            REQUIRE(!vm.equal_flag);
        }
    }
}

TEST_CASE("JMPE execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        PREPARE_VM(BS({15, i, 0, 0, 15, i, 0, 0, 15, i, 0, 0}), 12);
        vm.registers[i] = 7;
        vm.equal_flag = true;
        vm_run_once(&vm);
        REQUIRE(vm.pc == 7);
    }
}

TEST_CASE("NOP execution") {
    // TODO: test NOP better
    PREPARE_VM(BS({16, 0, 0, 0,16, 0, 0, 0}), 8);
    vm_run_once(&vm);
    REQUIRE(vm.pc == 4);
}

TEST_CASE("ALOC execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        PREPARE_VM(BS({17, i, 0, 0}), 4);
        size_t starting_size = vm.heap.array_len;
        vm.registers[i] = 1024;
        vm_run_once(&vm);
        REQUIRE(vm.heap.array_len == starting_size + 1024);
    }
}

TEST_CASE("INC execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        PREPARE_VM(BS({18, i, 0, 0}), 4);
        vm.registers[i] = 16;
        vm_run_once(&vm);
        REQUIRE(vm.registers[i] == 17);
    }
}

TEST_CASE("DEC execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        PREPARE_VM(BS({19, i, 0, 0}), 4);
        vm.registers[i] = 16;
        vm_run_once(&vm);
        REQUIRE(vm.registers[i] == 15);
    }
}

TEST_CASE("DJMPE execution") {
    // TOOD: test DJMPE
}

TEST_CASE("PRTS execution") {
    // TODO: test PTRS
}

TEST_CASE("LOADF64 execution") {
    // TODO: WTF is a 16 bit float?
//    for (u_int8_t i = 0; i < 32; ++i) {
//        PREPARE_VM(BS({22, i, 105, 64}), 4)
//        vm_run_once(&vm);
//        printf("%d->%lf\n", i, vm.float_registers[i]);
//        REQUIRE(vm.float_registers[i] == 200.0);
//    }
}

TEST_CASE("ADDF64 execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        for (u_int8_t j = 0; j < 32; ++j) {
            for (u_int8_t k = 0; k < 32; ++k) {
                PREPARE_VM(BS({23, i, j, k}), 4)
                vm.float_registers[i] = 10;
                vm.float_registers[j] = 5;
                vm_run_once(&vm);
                if (i != j)
                    REQUIRE(vm.float_registers[k] == 15);
                else
                    REQUIRE(vm.float_registers[k] == 10);
            }
        }
    }
}

TEST_CASE("SUBF64 execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        for (u_int8_t j = 0; j < 32; ++j) {
            for (u_int8_t k = 0; k < 32; ++k) {
                PREPARE_VM(BS({24, i, j, k}), 4)
                vm.float_registers[i] = 10;
                vm.float_registers[j] = 5;
                vm_run_once(&vm);
                if (i != j)
                    REQUIRE(vm.float_registers[k] == 5);
                else
                    REQUIRE(vm.float_registers[k] == 0);
            }
        }
    }
}

TEST_CASE("MULF64 execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        for (u_int8_t j = 0; j < 32; ++j) {
            for (u_int8_t k = 0; k < 32; ++k) {
                PREPARE_VM(BS({25, i, j, k}), 4)
                vm.float_registers[i] = 10;
                vm.float_registers[j] = 5;
                vm_run_once(&vm);
                if (i != j)
                    REQUIRE(vm.float_registers[k] == 50);
                else
                    REQUIRE(vm.float_registers[k] == 25);
            }
        }
    }
}

TEST_CASE("DIVF64 execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        for (u_int8_t j = 0; j < 32; ++j) {
            for (u_int8_t k = 0; k < 32; ++k) {
                PREPARE_VM(BS({26, i, j, k}), 4)
                vm.float_registers[i] = 10;
                vm.float_registers[j] = 2;
                vm_run_once(&vm);
                if (i != j) {
                    REQUIRE(vm.float_registers[k] == 5);
                } else {
                    REQUIRE(vm.float_registers[k] == 1);
                }
            }
        }
    }
}

TEST_CASE("EQF64 execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        for (u_int8_t j = 0; j < 32; ++j) {
            PREPARE_VM(BS({27, i, j, 0, 27, i, j, 0}), 8);
            vm.float_registers[i] = 10;
            vm.float_registers[j] = 10;
            vm_run_once(&vm);
            REQUIRE(vm.equal_flag);

            vm.float_registers[j] = 20;
            vm_run_once(&vm);
            if (i != j) {
                REQUIRE(!vm.equal_flag);
            } else {
                REQUIRE(vm.equal_flag);
            }
        }
    }
}

TEST_CASE("NEQF64 execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        for (u_int8_t j = 0; j < 32; ++j) {
            PREPARE_VM(BS({28, i, j, 0, 28, i, j, 0}), 8);
            vm.float_registers[i] = 10;
            vm.float_registers[j] = 20;
            vm_run_once(&vm);
            if (i != j) {
                REQUIRE(vm.equal_flag);
            } else {
                REQUIRE(!vm.equal_flag);
            }

            vm.float_registers[j] = 10;
            vm_run_once(&vm);
            REQUIRE(!vm.equal_flag);
        }
    }
}

TEST_CASE("GTF64 execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        for (u_int8_t j = 0; j < 32; ++j) {
            PREPARE_VM(BS({29, i, j, 0, 29, i, j, 0, 29, i, j, 0}), 12);
            vm.float_registers[i] = 20;
            vm.float_registers[j] = 10;
            vm_run_once(&vm);
            if (i != j) {
                REQUIRE(vm.equal_flag);
            } else {
                REQUIRE(!vm.equal_flag);
            }

            vm.float_registers[i] = 10;
            vm_run_once(&vm);
            REQUIRE(!vm.equal_flag);


            vm.float_registers[i] = 5;
            vm_run_once(&vm);
            REQUIRE(!vm.equal_flag);
        }
    }
}

TEST_CASE("GTEF64 execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        for (u_int8_t j = 0; j < 32; ++j) {
            PREPARE_VM(BS({30, i, j, 0, 30, i, j, 0, 30, i, j, 0}), 12);
            vm.float_registers[i] = 20;
            vm.float_registers[j] = 10;
            vm_run_once(&vm);
            REQUIRE(vm.equal_flag);

            vm.float_registers[i] = 10;
            vm_run_once(&vm);
            REQUIRE(vm.equal_flag);

            vm.float_registers[i] = 5;
            vm_run_once(&vm);
            if (i != j) {
                REQUIRE(!vm.equal_flag);
            } else {
                REQUIRE(vm.equal_flag);
            }
        }
    }
}

TEST_CASE("LTF64 execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        for (u_int8_t j = 0; j < 32; ++j) {
            PREPARE_VM(BS({31, i, j, 0, 31, i, j, 0, 31, i, j, 0}), 12);
            vm.float_registers[i] = 20;
            vm.float_registers[j] = 10;
            vm_run_once(&vm);
            REQUIRE(!vm.equal_flag);

            vm.float_registers[i] = 10;
            vm_run_once(&vm);
            REQUIRE(!vm.equal_flag);


            vm.float_registers[i] = 5;
            vm_run_once(&vm);
            if (i != j) {
                REQUIRE(vm.equal_flag);
            } else {
                REQUIRE(!vm.equal_flag);
            }
        }
    }
}

TEST_CASE("LTEF64 execution") {
    for (u_int8_t i = 0; i < 32; ++i) {
        for (u_int8_t j = 0; j < 32; ++j) {
            PREPARE_VM(BS({32, i, j, 0, 32, i, j, 0, 32, i, j, 0}), 12);
            vm.float_registers[i] = 20;
            vm.float_registers[j] = 10;
            vm_run_once(&vm);
            if (i != j) {
                REQUIRE(!vm.equal_flag);
            } else {
                REQUIRE(vm.equal_flag);
            }

            vm.float_registers[i] = 10;
            vm_run_once(&vm);
            REQUIRE(vm.equal_flag);

            vm.float_registers[i] = 5;
            vm_run_once(&vm);
            REQUIRE(vm.equal_flag);
        }
    }
}

TEST_CASE("SHL execution") {
    // TODO: test shifts
}

TEST_CASE("SHR execution") {
    // TODO: test shifts
}

TEST_CASE("AND execution") {

}

TEST_CASE("OR execution") {

}

TEST_CASE("XOR execution") {

}

TEST_CASE("NOT execution") {

}

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