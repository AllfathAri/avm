//
// Created by allfathari on 6/21/19.
//

#ifndef AVM_ASSEMBLER_H
#define AVM_ASSEMBLER_H

//region Errors

#include <zconf.h>
#include "lib/mpc.h"

typedef enum Assembler_Error_Flag {
    NO_SEGMENT_DECLARATION_FOUND,
    STRING_CONSTANT_DECLARED_WITHOUT_LABEL,
    SYMBOL_ALREADY_DECLARED,
    UNKNOWN_DIRECTIVE_FOUND,
    NON_OPCODE_IN_OPCODE_FIELD,
    INSUFFICIENT_SECTIONS,
    PARSE_ERROR
} Assembler_Error_Flag;

typedef struct No_Segment_Declaration_Found {
    u_int32_t instruction;
} No_Segment_Declaration_Found;

typedef struct String_Constant_Declared_Without_Label {
    u_int32_t instruction;
} String_Constant_Declared_Without_Label;

typedef struct Symbol_Already_Declared {
} Symbol_Already_Declared;

typedef struct Unknown_Directive_Found {
    const char *directive;
} Unknown_Directive_Found;

typedef struct Non_Opcode_In_Opcode_Field {

} Non_Opcode_In_Opcode_Field;

typedef struct Insufficient_Sections {

} Insufficient_Sections;

typedef struct Parse_Error {
    const char *error;
} Parse_Error;

typedef struct Assembler_Error {
    Assembler_Error_Flag flag;
    union Error {
        No_Segment_Declaration_Found no_segment_declaration_found;
        String_Constant_Declared_Without_Label string_constant_declared_without_label;
        Symbol_Already_Declared symbol_already_declared;
        Unknown_Directive_Found unknown_directive_found;
        Non_Opcode_In_Opcode_Field non_opcode_in_opcode_field;
        Insufficient_Sections insufficient_sections;
        Parse_Error parse_error;
    } error;
} Assembler_Error;

void assembler_error_print(Assembler_Error *, char *);

void assembler_error_description(Assembler_Error *, char *);

//endregion

typedef struct Assembler_Parser {
    mpc_parser_t *comment;
    mpc_parser_t *reg;
    mpc_parser_t *label_declaration;
    mpc_parser_t *label_usage;
    mpc_parser_t *opcode;
    mpc_parser_t *integer_operand;
    mpc_parser_t *float_operand;
    mpc_parser_t *irstring;
    mpc_parser_t *operand;
    mpc_parser_t *directive_declaration;
    mpc_parser_t *directive_combined;
    mpc_parser_t *directive;
    mpc_parser_t *instruction_combined;
    mpc_parser_t *instruction;
    mpc_parser_t *program;
} Assembler_Parser;

void assembler_parser_init(Assembler_Parser *);
void assembler_parser_free(Assembler_Parser *);

#endif //AVM_ASSEMBLER_H

