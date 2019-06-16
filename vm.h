//
// Created by allfathari on 6/12/19.
//

#ifndef AVM_VM_H
#define AVM_VM_H

#include <sys/types.h>
#include <stdbool.h>
#include "instructions.h"
#include "collections.h"

typedef struct VM {
    int32_t registers[32];
    double float_registers[32];
    Byte_Vector program;
    size_t pc;
    size_t sp;
    size_t bp;
    Byte_Vector heap;
    Int_Stack stack;
    u_int32_t remainder;
    bool equal_flag;
    size_t loop_counter;
} VM;

void vm_init(VM *);

void vm_free(VM *);

void vm_run(VM *);

void vm_run_once(VM *);

void vm_add_byte(VM *, u_int8_t);

void vm_add_bytes(VM *, Byte_Vector *);

static void vm_execute_instruction(VM *);

static u_int8_t vm_next_8_bits(VM *vm);

static u_int8_t vm_next_16_bits(VM *vm);

#endif //AVM_VM_H
