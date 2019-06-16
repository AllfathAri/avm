//
// Created by allfathari on 6/16/19.
//

#include "lib/catch.hpp"
#include <string.h>

extern "C" {
    #include "instructions.h"
}

TEST_CASE("Create instruction") {
    for (int i = 0; i < OPCODE_COUNT; ++i) {
        auto oc = (Opcode) i;
        Instruction ins = instruction_make(oc);
        REQUIRE(ins.opcode == oc);
    }
}

TEST_CASE("String to instruction conversion") {
    REQUIRE(opcode_from_str("LOAD") == LOAD);
    REQUIRE(opcode_from_str("ADD") == ADD);
    REQUIRE(opcode_from_str("SUB") == SUB);
    REQUIRE(opcode_from_str("MUL") == MUL);
    REQUIRE(opcode_from_str("DIV") == DIV);
    REQUIRE(opcode_from_str("HLT") == HLT);
    REQUIRE(opcode_from_str("JMP") == JMP);
    REQUIRE(opcode_from_str("JMPF") == JMPF);
    REQUIRE(opcode_from_str("JMPB") == JMPB);
    REQUIRE(opcode_from_str("EQ") == EQ);
    REQUIRE(opcode_from_str("NEQ") == NEQ);
    REQUIRE(opcode_from_str("GTE") == GTE);
    REQUIRE(opcode_from_str("LTE") == LTE);
    REQUIRE(opcode_from_str("LT") == LT);
    REQUIRE(opcode_from_str("GT") == GT);
    REQUIRE(opcode_from_str("JMPE") == JMPE);
    REQUIRE(opcode_from_str("NOP") == NOP);
    REQUIRE(opcode_from_str("ALOC") == ALOC);
    REQUIRE(opcode_from_str("INC") == INC);
    REQUIRE(opcode_from_str("DEC") == DEC);
    REQUIRE(opcode_from_str("DJMPE") == DJMPE);
    REQUIRE(opcode_from_str("PRTS") == PRTS);
    REQUIRE(opcode_from_str("LOADF64") == LOADF64);
    REQUIRE(opcode_from_str("ADDF64") == ADDF64);
    REQUIRE(opcode_from_str("SUBF64") == SUBF64);
    REQUIRE(opcode_from_str("MULF64") == MULF64);
    REQUIRE(opcode_from_str("DIVF64") == DIVF64);
    REQUIRE(opcode_from_str("EQF64") == EQF64);
    REQUIRE(opcode_from_str("NEQF64") == NEQF64);
    REQUIRE(opcode_from_str("GTF64") == GTF64);
    REQUIRE(opcode_from_str("GTEF64") == GTEF64);
    REQUIRE(opcode_from_str("LTF64") == LTF64);
    REQUIRE(opcode_from_str("LTEF64") == LTEF64);
    REQUIRE(opcode_from_str("SHL") == SHL);
    REQUIRE(opcode_from_str("SHR") == SHR);
    REQUIRE(opcode_from_str("AND") == AND);
    REQUIRE(opcode_from_str("OR") == OR);
    REQUIRE(opcode_from_str("XOR") == XOR);
    REQUIRE(opcode_from_str("NOT") == NOT);
    REQUIRE(opcode_from_str("LUI") == LUI);
    REQUIRE(opcode_from_str("CLOOP") == CLOOP);
    REQUIRE(opcode_from_str("LOOP") == LOOP);
    REQUIRE(opcode_from_str("LOADM") == LOADM);
    REQUIRE(opcode_from_str("SETM") == SETM);
    REQUIRE(opcode_from_str("PUSH") == PUSH);
    REQUIRE(opcode_from_str("POP") == POP);
    REQUIRE(opcode_from_str("CALL") == CALL);
    REQUIRE(opcode_from_str("RET") == RET);
    REQUIRE(opcode_from_str("IGL") == IGL);
}

TEST_CASE("Illegal opcode conversion") {
    REQUIRE(opcode_from_str("123") == IGL);
    REQUIRE(opcode_from_str("ABC") == IGL);
    REQUIRE(opcode_from_str("!@#") == IGL);
}

TEST_CASE("byte to opcode conversion") {
    REQUIRE(opcode_from_u8(0) == LOAD);
    REQUIRE(opcode_from_u8(1) == ADD);
    REQUIRE(opcode_from_u8(2) == SUB);
    REQUIRE(opcode_from_u8(3) == MUL);
    REQUIRE(opcode_from_u8(4) == DIV);
    REQUIRE(opcode_from_u8(5) == HLT);
    REQUIRE(opcode_from_u8(6) == JMP);
    REQUIRE(opcode_from_u8(7) == JMPF);
    REQUIRE(opcode_from_u8(8) == JMPB);
    REQUIRE(opcode_from_u8(9) == EQ);
    REQUIRE(opcode_from_u8(10) == NEQ);
    REQUIRE(opcode_from_u8(11) == GTE);
    REQUIRE(opcode_from_u8(12) == LTE);
    REQUIRE(opcode_from_u8(13) == LT);
    REQUIRE(opcode_from_u8(14) == GT);
    REQUIRE(opcode_from_u8(15) == JMPE);
    REQUIRE(opcode_from_u8(16) == NOP);
    REQUIRE(opcode_from_u8(17) == ALOC);
    REQUIRE(opcode_from_u8(18) == INC);
    REQUIRE(opcode_from_u8(19) == DEC);
    REQUIRE(opcode_from_u8(20) == DJMPE);
    REQUIRE(opcode_from_u8(21) == PRTS);
    REQUIRE(opcode_from_u8(22) == LOADF64);
    REQUIRE(opcode_from_u8(23) == ADDF64);
    REQUIRE(opcode_from_u8(24) == SUBF64);
    REQUIRE(opcode_from_u8(25) == MULF64);
    REQUIRE(opcode_from_u8(26) == DIVF64);
    REQUIRE(opcode_from_u8(27) == EQF64);
    REQUIRE(opcode_from_u8(28) == NEQF64);
    REQUIRE(opcode_from_u8(29) == GTF64);
    REQUIRE(opcode_from_u8(30) == GTEF64);
    REQUIRE(opcode_from_u8(31) == LTF64);
    REQUIRE(opcode_from_u8(32) == LTEF64);
    REQUIRE(opcode_from_u8(33) == SHL);
    REQUIRE(opcode_from_u8(34) == SHR);
    REQUIRE(opcode_from_u8(35) == AND);
    REQUIRE(opcode_from_u8(36) == OR);
    REQUIRE(opcode_from_u8(37) == XOR);
    REQUIRE(opcode_from_u8(38) == NOT);
    REQUIRE(opcode_from_u8(39) == LUI);
    REQUIRE(opcode_from_u8(40) == CLOOP);
    REQUIRE(opcode_from_u8(41) == LOOP);
    REQUIRE(opcode_from_u8(42) == LOADM);
    REQUIRE(opcode_from_u8(43) == SETM);
    REQUIRE(opcode_from_u8(44) == PUSH);
    REQUIRE(opcode_from_u8(45) == POP);
    REQUIRE(opcode_from_u8(46) == CALL);
    REQUIRE(opcode_from_u8(47) == RET);
    REQUIRE(opcode_from_u8(48) == IGL);
}

