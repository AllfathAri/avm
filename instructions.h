//
// Created by allfathari on 6/12/19.
//

#ifndef AVM_INSTRUCTIONS_H
#define AVM_INSTRUCTIONS_H

#include <sys/types.h>

typedef enum Opcode {
    LOAD = 0,
    ADD,
    SUB,
    MUL,
    DIV,
    HLT,
    JMP,
    JMPF,
    JMPB,
    EQ,
    NEQ,
    GTE,
    LTE,
    LT,
    GT,
    JMPE,
    NOP,
    ALOC,
    INC,
    DEC,
    DJMPE,
    PRTS,
    LOADF64,
    ADDF64,
    SUBF64,
    MULF64,
    DIVF64,
    EQF64,
    NEQF64,
    GTF64,
    GTEF64,
    LTF64,
    LTEF64,
    SHL,
    SHR,
    AND,
    OR,
    XOR,
    NOT,
    LUI,
    CLOOP,
    LOOP,
    LOADM,
    SETM,
    PUSH,
    POP,
    CALL,
    RET,
    IGL,
} Opcode;

#define OPCODE_COUNT 48

Opcode opcode_from_u8(u_int8_t);

Opcode opcode_from_str(const char *);

typedef struct Instruction {
    Opcode opcode;
} Instruction;

Instruction instruction_make(Opcode);

#endif //AVM_INSTRUCTIONS_H
