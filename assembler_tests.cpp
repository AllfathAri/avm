//
// Created by allfathari on 6/21/19.
//

#include "lib/catch.hpp"
#include <string.h>

extern "C" {
#include "assembler.h"
}

#define PARSER_INIT(name, str, pname)                      \
Assembler_Parser parser;                                   \
assembler_parser_init(&parser);                            \
mpc_result_t result;                                       \
int success = mpc_parse(name, str, parser.pname, &result); \
/* bumper line to support last backslash, leave empty! */

#define PARSER_FREE()                           \
if (success) {                                  \
    mpc_ast_delete((mpc_ast_t*) result.output); \
}   else {                                      \
    mpc_err_print((mpc_err_t*) result.error);   \
    mpc_err_delete((mpc_err_t*) result.error);  \
}                                               \
assembler_parser_free(&parser);                 \
/* bumper line to support last backslash, leave empty! */

TEST_CASE("Parse comment") {
    PARSER_INIT("comment", "; some text", comment)
    PARSER_FREE()
    REQUIRE(success);
}

TEST_CASE("Parse register") {
    PARSER_INIT("register", "$31", reg)
    PARSER_FREE()
    REQUIRE(success);
}

TEST_CASE("Parse label declaration") {
    PARSER_INIT("label_declaration", "myLabel:", label_declaration)
    PARSER_FREE()
    REQUIRE(success);
}

TEST_CASE("Parse label usage") {
    PARSER_INIT("label_usage", "@myLabel", label_usage)
    PARSER_FREE()
    REQUIRE(success);
}

TEST_CASE("Parse opcode") {
    PARSER_INIT("opcode", "ADD2f", opcode)
    PARSER_FREE()
    REQUIRE(success);
}

TEST_CASE("Parse integer operand") {
    PARSER_INIT("integer_operand", "#123987", integer_operand)
    PARSER_FREE()
    REQUIRE(success);
}

TEST_CASE("Parse float operand") {
    PARSER_INIT("float_operand", "#123.987", float_operand)
    PARSER_FREE()
    REQUIRE(success);
}

TEST_CASE("Parse IR string") {
    PARSER_INIT("irstring", "\'text\'", irstring)
    PARSER_FREE()
    REQUIRE(success);
}

TEST_CASE("Parse operand") {
    Assembler_Parser parser;
    assembler_parser_init(&parser);

    const char *strs[5] = {
            "#123.987",
            "#123",
            "@myLabel",
            "$31",
            "\'test\'"
    };

    for (int i = 0; i < 5; ++i) {
        mpc_result_t result;
        int success;

        success = mpc_parse("operand", strs[i], parser.operand, &result);
        if (success) {
            mpc_ast_delete((mpc_ast_t *) result.output);
        } else {
            mpc_err_print((mpc_err_t *) result.error);
            mpc_err_delete((mpc_err_t *) result.error);
        }
        REQUIRE(success);
    }

    assembler_parser_free(&parser);
}

TEST_CASE("Parse directive declaration") {
    PARSER_INIT("directive_declaration", ".data", directive_declaration)
    PARSER_FREE()
    REQUIRE(success);
}

TEST_CASE("Parse directive combined") {
    PARSER_INIT("directive_combined", "test: .asciiz 'Hello'", directive_combined)
    PARSER_FREE()
    REQUIRE(success);
}

TEST_CASE("Parse directive") {
    PARSER_INIT("directive", "test: .asciiz 'Hello'", directive)
    PARSER_FREE()
    REQUIRE(success);
}

TEST_CASE("Parse instruction combined") {
    Assembler_Parser parser;
    assembler_parser_init(&parser);

    const char *strs[7] = {
            "load $0 #100\n",
            "hlt",
            "add $0 $1 $2\n",
            "; this is a test\nadd $0 $1 $2\n",
            "add $0 $1 $2 ; this is a test\n",
            "cloop #10\n",
            "call @test\n"
    };

    for (int i = 0; i < 7; ++i) {
        mpc_result_t result;
        int success;

        success = mpc_parse("instruction_combined", strs[i], parser.instruction_combined, &result);
        if (success) {
            mpc_ast_delete((mpc_ast_t *) result.output);
        } else {
            mpc_err_print((mpc_err_t *) result.error);
            mpc_err_delete((mpc_err_t *) result.error);
        }
        REQUIRE(success);
    }

    assembler_parser_free(&parser);
}

TEST_CASE("Parse instruction") {
    Assembler_Parser parser;
    assembler_parser_init(&parser);

    const char *strs[7] = {
            "load $0 #100\n",
            "hlt",
            "add $0 $1 $2\n",
            "; this is a test\nadd $0 $1 $2\n",
            "add $0 $1 $2 ; this is a test\n",
            "cloop #10\n",
            "call @test\n"
    };

    for (int i = 0; i < 7; ++i) {
        mpc_result_t result;
        int success;

        success = mpc_parse("instruction", strs[i], parser.instruction, &result);
        if (success) {
            mpc_ast_delete((mpc_ast_t *) result.output);
        } else {
            mpc_err_print((mpc_err_t *) result.error);
            mpc_err_delete((mpc_err_t *) result.error);
        }
        REQUIRE(success);
    }

    assembler_parser_free(&parser);
}

TEST_CASE("Parse program") {
    Assembler_Parser parser;
    assembler_parser_init(&parser);

    const char *strs[5] = {
            "load $0 #100\n",
            "load $0 #100\n",
            ".data\nhello: .asciiz 'Hello everyone!'\n.code\nhlt",
            ".data\n.code\nload $0 #-50000",
            ".data\n.code\ncloop #10"
    };

    for (int i = 0; i < 5; ++i) {
        mpc_result_t result;
        int success;

        success = mpc_parse("program", strs[i], parser.program, &result);
        if (success) {
            mpc_ast_delete((mpc_ast_t *) result.output);
        } else {
            mpc_err_print((mpc_err_t *) result.error);
            mpc_err_delete((mpc_err_t *) result.error);
        }
        REQUIRE(success);
    }

    assembler_parser_free(&parser);
}