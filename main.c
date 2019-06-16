#include <stdio.h>
#include "vm.h"
#include <string.h>

int main() {

    const char *codeStrs[] = {
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

    for (int i = 0; i < OPCODE_COUNT + 1; ++i) {
        printf("REQUIRE(opcode_from_u8(%d) == %s);\n", i, codeStrs[i]);
    }

    return 0;
}