//
// Created by allfathari on 6/21/19.
//

#ifndef AVM_ASSEMBLER_H
#define AVM_ASSEMBLER_H

#include <zconf.h>
#include "lib/mpc.h"
#include "instructions.h"

//region Tokens

typedef enum Assembler_Token_Flag {
    OP,
    REGISTER,
    INTEGER_OPERAND,
    FLOAT_OPERAND,
    LABEL_DECLARATION,
    LABEL_USAGE,
    DIRECTIVE,
    IR_STRING,
    COMMENT
} Assembler_Token_Flag;

typedef struct Op {
    Opcode code;
} Op;

typedef struct Register {
    size_t reg_num;
} Register;

typedef struct Integer_Operand {
    u_int32_t value;
} Integer_Operand;

typedef struct Float_Operand {
    double value;
} Float_Operand;

typedef struct Label_Declaration {
    char *name;
} Label_Declaration;

typedef struct Label_Usage {
    char *name;
} Label_Usage;

typedef struct Directive {
    char *name;
} Directive;

typedef struct Ir_String {
    char *name;
} Ir_String;

typedef struct Comment {

} Comment;

typedef struct Assembler_Token {
    Assembler_Token_Flag flag;
    union Token {
        Op op;
        Register reg;
        Integer_Operand integer_operand;
        Float_Operand float_operand;
        Label_Declaration label_declaration;
        Label_Usage label_usage;
        Directive directive;
        Ir_String ir_string;
        Comment comment;
    } token;
} Assembler_Token;

Assembler_Token *op_new(Opcode opcode);

Assembler_Token *reg_new(size_t reg_num);

Assembler_Token *i_op_new(int32_t value);

Assembler_Token *f_op_new(double value);

Assembler_Token *ldec_new(const char* name);

Assembler_Token *lus_new(const char *name);

Assembler_Token *directive_new(const char *name);

Assembler_Token *ir_string_new(const char *name);

Assembler_Token *comment_new();

void assembler_token_delete(Assembler_Token *token);

//endregion

//region Parsers

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

//endregion

//region Errors

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
#endif //AVM_ASSEMBLER_H

