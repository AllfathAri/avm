#include <stdio.h>
#include "vm.h"

const unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5u) + hash) + c;
    return hash;
}

int main() {
    const char *opCodes[] = {
            "LOAD",
            "ADD",
            "SUB",
            "MUL",
            "DIV",
            "HLT",
            "JMP",
            "JMPF",
            "JMPB",
            "EQ",
            "NEQ",
            "GTE",
            "LTE",
            "LT",
            "GT",
            "JMPE",
            "NOP",
            "ALOC",
            "INC",
            "DEC",
            "DJMPE",
            "PRTS",
            "LOADF64",
            "ADDF64",
            "SUBF64",
            "MULF64",
            "DIVF64",
            "EQF64",
            "NEQF64",
            "GTF64",
            "GTEF64",
            "LTF64",
            "LTEF64",
            "SHL",
            "SHR",
            "AND",
            "OR",
            "XOR",
            "NOT",
            "LUI",
            "CLOOP",
            "LOOP",
            "LOADM",
            "SETM",
            "PUSH",
            "POP",
            "CALL",
            "RET",
            "IGL"
    };

    for (int i = 0; i < OPCODE_COUNT; ++i) {
        const char *opCode = opCodes[i];
        printf("void vm_dispatch_%s(VM *vm){}\n", opCode);
    }

    return 0;
}