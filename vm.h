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
    u_int8_t *program;
    size_t  program_len;
    size_t pc;
    size_t sp;
    size_t bp;
    Int_Stack *stack;
    u_int32_t remainder;
    bool equal_flag;
    size_t loop_counter;
} VM;

VM* vm_new();

void vm_delete(VM*);

void vm_run(VM*);

Opcode vm_decode_opcode(VM*);

void vm_dispatch_opcode(VM*, Opcode);

u_int8_t vm_next_8_bits(VM*);

u_int8_t vm_next_16_bits(VM*);


#endif //AVM_VM_H
