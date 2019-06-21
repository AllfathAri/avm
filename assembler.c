//
// Created by allfathari on 6/21/19.
//
#include <stdio.h>
#include "assembler.h"

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

void assembler_parser_init(Assembler_Parser *parser) {
    parser->comment = mpc_new("comment");
    parser->reg = mpc_new("register");
    parser->label_declaration = mpc_new("label-declaration");
    parser->label_usage = mpc_new("label-usage");
    parser->opcode = mpc_new("opcode");
    parser->integer_operand = mpc_new("integer-operand");
    parser->float_operand = mpc_new("float-operand");
    parser->irstring = mpc_new("irstring");
    parser->operand = mpc_new("operand");
    parser->directive_declaration = mpc_new("directive-declaration");
    parser->directive_combined = mpc_new("directive-combined");
    parser->directive = mpc_new("directive");
    parser->instruction_combined = mpc_new("instruction-combined");
    parser->instruction = mpc_new("instruction");
    parser->program = mpc_new("program");


    mpca_lang(MPCA_LANG_DEFAULT,

              " comment                 : /;[^\\r\\n]*/ ;                              "
              " register                : /\\$[0-9]+/ ;                                "
              " label-declaration       : /[a-zA-Z0-9_+\\-*\\/\\\\=<>!&]+:/ ;          "
              " label-usage             : /[a-zA-Z0-9_+\\-*\\/\\\\=<>!&]+@/ ;          "
              " opcode                  : /[a-zA-Z0-9]+/ ;                             "
              " integer-operand         : /#\\-?[0-9]+/                     ;          "
              " float-operand           : /#\\-?[0-9].[0-9]+/ ;                        "
              " irstring                : /\"(\\\\.|[^\"])*\"/ ;                       "
              " operand                 : <integer-operand> | <float-operand>          "
              "                         | <label-usage>     | <register>               "
              "                         | <irstring> ;                                 "
              " directive-declaration   : /.[a-zA-Z0-9]+/ ;                            "
              " directive-combined      : <label-declaration>? <directive-declaration> "
              "                           <operand>? <operand>? <operand>? ;           "
              " directive               : <directive-combined> ;                       "
              " instruction-combined    : <comment>? <label-declaration>? <opcode>     "
              "                           <operand>? <operand>? <operand>? <comment>? ;"
              " instruction             : <instruction-combined> ;                     "
              " program                 : ( <instruction> | <directive> )+ ;           ",

              parser->comment,
              parser->reg,
              parser->label_declaration,
              parser->label_usage,
              parser->opcode,
              parser->integer_operand,
              parser->float_operand,
              parser->irstring,
              parser->opcode,
              parser->directive_declaration,
              parser->directive_combined,
              parser->directive,
              parser->instruction_combined,
              parser->instruction,
              parser->program,
              NULL);


}

void assembler_parser_free(Assembler_Parser *parser) {
    mpc_delete(parser->comment);
    mpc_delete(parser->reg);
    mpc_delete(parser->label_declaration);
    mpc_delete(parser->label_usage);
    mpc_delete(parser->opcode);
    mpc_delete(parser->integer_operand);
    mpc_delete(parser->float_operand);
    mpc_delete(parser->irstring);
    mpc_delete(parser->opcode);
    mpc_delete(parser->directive_declaration);
    mpc_delete(parser->directive);
    mpc_delete(parser->instruction_combined);
    mpc_delete(parser->instruction);
    mpc_delete(parser->program);
}

//endregion


