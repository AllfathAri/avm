//
// Created by allfathari on 6/12/19.
//

#include "instructions.h"

Instruction instruction_make(Opcode opcode) {
    Instruction result = {
            opcode
    };

    return result;
}

Opcode opcode_from_u8(u_int8_t v) {
    u_int8_t legalOpCodesCount = OPCODE_COUNT;
    if (v < legalOpCodesCount) return (Opcode) v;
    return IGL;
}

#define LOAD_HASH 6384260357
#define ADD_HASH 193450094
#define SUB_HASH 193470255
#define MUL_HASH 193463731
#define DIV_HASH 193453544
#define HLT_HASH 193457997
#define JMP_HASH 193460204
#define JMPF_HASH 6384186802
#define JMPB_HASH 6384186798
#define EQ_HASH 5862267
#define NEQ_HASH 193464297
#define GTE_HASH 193457157
#define LTE_HASH 193462602
#define LT_HASH 5862501
#define GT_HASH 5862336
#define JMPE_HASH 6384186801
#define NOP_HASH 193464626
#define ALOC_HASH 6383862244
#define INC_HASH 193459135
#define DEC_HASH 193453393
#define DJMPE_HASH 210670938261
#define PRTS_HASH 6384408014
#define LOADF64_HASH 229431164527573
#define ADDF64_HASH 6952016106142
#define SUBF64_HASH 6952740631999
#define MULF64_HASH 6952506179011
#define DIVF64_HASH 6952140088792
#define EQF64_HASH 210672367243
#define NEQF64_HASH 6952526519353
#define GTF64_HASH 210674846896
#define GTEF64_HASH 6952269929173
#define LTF64_HASH 210680776501
#define LTEF64_HASH 6952465606138
#define SHL_HASH 193469836
#define SHR_HASH 193469842
#define AND_HASH 193450424
#define OR_HASH 5862598
#define XOR_HASH 193475518
#define NOT_HASH 193464630
#define LUI_HASH 193462639
#define CLOOP_HASH 210669826370
#define LOOP_HASH 6384260831
#define LOADM_HASH 210680591858
#define SETM_HASH 6384501662
#define PUSH_HASH 6384411237
#define POP_HASH 193466804
#define CALL_HASH 6383922049
#define RET_HASH 193468656
#define IGL_HASH 193458913

const unsigned long str_hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5u) + hash) + c;
    return hash;
}

Opcode opcode_from_str(const char *v) {
    switch (str_hash(v)) {
        case LOAD_HASH:
            return LOAD;
        case ADD_HASH:
            return ADD;
        case SUB_HASH:
            return SUB;
        case MUL_HASH:
            return MUL;
        case DIV_HASH:
            return DIV;
        case HLT_HASH:
            return HLT;
        case JMP_HASH:
            return JMP;
        case JMPF_HASH:
            return JMPF;
        case JMPB_HASH:
            return JMPB;
        case EQ_HASH:
            return EQ;
        case NEQ_HASH:
            return NEQ;
        case GTE_HASH:
            return GTE;
        case LTE_HASH:
            return LTE;
        case LT_HASH:
            return LT;
        case GT_HASH:
            return GT;
        case JMPE_HASH:
            return JMPE;
        case NOP_HASH:
            return NOP;
        case ALOC_HASH:
            return ALOC;
        case INC_HASH:
            return INC;
        case DEC_HASH:
            return DEC;
        case DJMPE_HASH:
            return DJMPE;
        case PRTS_HASH:
            return PRTS;
        case LOADF64_HASH:
            return LOADF64;
        case ADDF64_HASH:
            return ADDF64;
        case SUBF64_HASH:
            return SUBF64;
        case MULF64_HASH:
            return MULF64;
        case DIVF64_HASH:
            return DIVF64;
        case EQF64_HASH:
            return EQF64;
        case NEQF64_HASH:
            return NEQF64;
        case GTF64_HASH:
            return GTF64;
        case GTEF64_HASH:
            return GTEF64;
        case LTF64_HASH:
            return LTF64;
        case LTEF64_HASH:
            return LTEF64;
        case SHL_HASH:
            return SHL;
        case SHR_HASH:
            return SHR;
        case AND_HASH:
            return AND;
        case OR_HASH:
            return OR;
        case XOR_HASH:
            return XOR;
        case NOT_HASH:
            return NOT;
        case LUI_HASH:
            return LUI;
        case CLOOP_HASH:
            return CLOOP;
        case LOOP_HASH:
            return LOOP;
        case LOADM_HASH:
            return LOADM;
        case SETM_HASH:
            return SETM;
        case PUSH_HASH:
            return PUSH;
        case POP_HASH:
            return POP;
        case CALL_HASH:
            return CALL;
        case RET_HASH:
            return RET;
        default:
            return IGL;
    }
}

#undef LOAD_HASH
#undef ADD_HASH
#undef SUB_HASH
#undef MUL_HASH
#undef DIV_HASH
#undef HLT_HASH
#undef JMP_HASH
#undef JMPF_HASH
#undef JMPB_HASH
#undef EQ_HASH
#undef NEQ_HASH
#undef GTE_HASH
#undef LTE_HASH
#undef LT_HASH
#undef GT_HASH
#undef JMPE_HASH
#undef NOP_HASH
#undef ALOC_HASH
#undef INC_HASH
#undef DEC_HASH
#undef DJMPE_HASH
#undef PRTS_HASH
#undef LOADF64_HASH
#undef ADDF64_HASH
#undef SUBF64_HASH
#undef MULF64_HASH
#undef DIVF64_HASH
#undef EQF64_HASH
#undef NEQF64_HASH
#undef GTF64_HASH
#undef GTEF64_HASH
#undef LTF64_HASH
#undef LTEF64_HASH
#undef SHL_HASH
#undef SHR_HASH
#undef AND_HASH
#undef OR_HASH
#undef XOR_HASH
#undef NOT_HASH
#undef LUI_HASH
#undef CLOOP_HASH
#undef LOOP_HASH
#undef LOADM_HASH
#undef SETM_HASH
#undef PUSH_HASH
#undef POP_HASH
#undef CALL_HASH
#undef RET_HASH
#undef IGL_HASH