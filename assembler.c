//
// Created by allfathari on 6/21/19.
//
#include <stdio.h>
#include "lib/mpc.h"
#include "assembler.h"

//region Tokens

Assembler_Token *op_new(Opcode opcode) {

}

Assembler_Token *reg_new(size_t reg_num) {

}

Assembler_Token *i_op_new(int32_t value) {

}

Assembler_Token *f_op_new(double value) {

}

Assembler_Token *ldec_new(const char *name) {

}

Assembler_Token *lus_new(const char *name) {

}

Assembler_Token *directive_new(const char *name) {

}

Assembler_Token *ir_string_new(const char *name) {

}

Assembler_Token *comment_new() {

}

void assembler_token_delete(Assembler_Token *token) {
    switch (token->flag) {

        case OP:
            break;

        case REGISTER:
            break;

        case INTEGER_OPERAND:
            break;

        case FLOAT_OPERAND:
            break;

        case LABEL_DECLARATION:
            free(token->token.label_declaration.name);
            break;

        case LABEL_USAGE:
            free(token->token.label_usage.name);
            break;

        case DIRECTIVE:
            free(token->token.directive.name);
            break;

        case IR_STRING:
            free(token->token.ir_string.name);
            break;

        case COMMENT:
            break;
    }

    free(token);
}

//endregion

//region Parsers

mpc_val_t *apply_comment(mpc_result_t input) {
    return comment_new();
}

typedef enum {
    STR2INT_SUCCESS,
    STR2INT_OVERFLOW,
    STR2INT_UNDERFLOW,
    STR2INT_INCONVERTIBLE
} str2int_errno;

str2int_errno str2int(int *out, char *s, int base) {
    char *end;
    if (s[0] == '\0' || isspace(s[0]))
        return STR2INT_INCONVERTIBLE;
    errno = 0;
    long l = strtol(s, &end, base);
    /* Both checks are needed because INT_MAX == LONG_MAX is possible. */
    if (l > INT_MAX || (errno == ERANGE && l == LONG_MAX))
        return STR2INT_OVERFLOW;
    if (l < INT_MIN || (errno == ERANGE && l == LONG_MIN))
        return STR2INT_UNDERFLOW;
    if (*end != '\0')
        return STR2INT_INCONVERTIBLE;
    *out = l;
    return STR2INT_SUCCESS;
}

mpc_val_t *apply_register(mpc_result_t *input) {
    int reg_num;
    str2int(&reg_num, (char *) &input[1], 10);

    return reg_new(reg_num);
}

Assembler_Token *apply_label_declaration(mpc_result_t *input) {
    char *input_str = (char *) input;
    int len = strlen(input_str); // already one less
    char *str = malloc(sizeof(char) * len);
    memcpy(str, input_str, sizeof(char) * len);
    str[len - 1] = '\0';

    return ldec_new(str);
}


void assembler_parser_init(Assembler_Parser *parser) {
    mpc_parser_t *comment = mpc_new("comment");
    mpc_parser_t *reg = mpc_new("register");
    mpc_parser_t *label_declaration = mpc_new("label_declaration");
    mpc_parser_t *label_usage = mpc_new("label_usage");
    mpc_parser_t *opcode = mpc_new("opcode");
    mpc_parser_t *integer_operand = mpc_new("integer_operand");
    mpc_parser_t *float_operand = mpc_new("float_operand");
    mpc_parser_t *irstring = mpc_new("irstring");
    mpc_parser_t *operand = mpc_new("operand");
    mpc_parser_t *directive_declaration = mpc_new("directive_declaration");
    mpc_parser_t *directive_combined = mpc_new("directive_combined");
    mpc_parser_t *directive = mpc_new("directive");
    mpc_parser_t *instruction_combined = mpc_new("instruction_combined");
    mpc_parser_t *instruction = mpc_new("instruction");
    mpc_parser_t *program = mpc_new("program");


    mpca_lang(MPCA_LANG_DEFAULT,

              " comment                : /;[^\\r\\n]*/ ;                               "
              " register               : /\\$[0-9]+/ ;                                 "
              " label_declaration      : /[a-zA-Z0-9]+:/ ;                             "
              " label_usage            : /@[a-zA-Z0-9]+/ ;                             "
              " opcode                 : /[a-zA-Z0-9]+/ ;                              "
              " integer_operand        : /#\\-?[0-9]+/ ;                               "
              " float_operand          : /#\\-?[0-9].[0-9]+/ ;                         "
              " irstring               : /\'(\\\\.|[^\'])*\'/ ;                        "
              " operand                : <float_operand>   | <integer_operand>         "
              "                        | <label_usage>     | <register>                "
              "                        | <irstring> ;                                  "
              " directive_declaration  : /.[a-zA-Z0-9]+/ ;                             "
              " directive_combined     : <label_declaration>? <directive_declaration>  "
              "                          <operand>? <operand>? <operand>? ;            "
              " directive              : <directive_combined> ;                        "
              " instruction_combined   : <comment>? <label_declaration>? <opcode>      "
              "                          <operand>? <operand>? <operand>? <comment>? ; "
              " instruction            : <instruction_combined> ;                      "
              " program                : ( <instruction> | <directive> )+ /$/ ;        ",
              comment,
              reg,
              label_declaration,
              label_usage,
              opcode,
              integer_operand,
              float_operand,
              irstring,
              operand,
              directive_declaration,
              directive_combined,
              directive,
              instruction_combined,
              instruction,
              program,
              NULL);

//    parser->comment = mpc_apply(comment, &apply_comment);

}

void assembler_parser_free(Assembler_Parser *parser) {
    mpc_cleanup(14,
                parser->comment,
                parser->reg,
                parser->label_declaration,
                parser->label_usage,
                parser->opcode,
                parser->integer_operand,
                parser->float_operand,
                parser->irstring,
                parser->operand,
                parser->directive_declaration,
                parser->directive_combined,
                parser->directive,
                parser->instruction_combined,
                parser->instruction,
                parser->program);
}

//endregion

//region Error

void assembler_error_print(Assembler_Error *error, char *str) {
    switch (error->flag) {

        case NO_SEGMENT_DECLARATION_FOUND:
            sprintf(str, "No segment declaration (e.g., .code, .data) prior to finding an opcode or other directive."
                         " Instruction # was %u:", error->error.no_segment_declaration_found.instruction);
            break;

        case STRING_CONSTANT_DECLARED_WITHOUT_LABEL:
            sprintf(str, "Found a string constant without a corresponding label."
                         " Instruction # was %u", error->error.string_constant_declared_without_label.instruction);
            break;

        case SYMBOL_ALREADY_DECLARED:
            sprintf(str, "This symbol was previously declared.");
            break;

        case UNKNOWN_DIRECTIVE_FOUND:
            sprintf(str, "Invalid or unknown directive found."
                         " Directive name was: %s", error->error.unknown_directive_found.directive);
            break;

        case NON_OPCODE_IN_OPCODE_FIELD:
            sprintf(str, "An non-opcode was found in an opcode field");
            break;

        case INSUFFICIENT_SECTIONS:
            sprintf(str, "Less than two sections/segments were found in the code");
            break;

        case PARSE_ERROR:
            sprintf(str, "There was an error parsing the code: %s", error->error.parse_error.error);
            break;
    }
}

void assembler_error_description(Assembler_Error *error, char *str) {
    switch (error->flag) {

        case NO_SEGMENT_DECLARATION_FOUND:
            sprintf(str, "No segment declaration (e.g., .code, .data) prior to finding an opcode or other directive.");
            break;

        case STRING_CONSTANT_DECLARED_WITHOUT_LABEL:
            sprintf(str, "Found a string constant without a corresponding label.");
            break;

        case SYMBOL_ALREADY_DECLARED:
            sprintf(str, "This symbol was previously declared.");
            break;

        case UNKNOWN_DIRECTIVE_FOUND:
            sprintf(str, "Invalid or unknown directive found.");
            break;

        case NON_OPCODE_IN_OPCODE_FIELD:
            sprintf(str, "A non-opcode was found in an opcode field");
            break;

        case INSUFFICIENT_SECTIONS:
            sprintf(str, "Less than two sections/segments were found in the code");
            break;

        case PARSE_ERROR:
            sprintf(str, "There was an error parsing the code");
            break;
    }
}

//endregion
