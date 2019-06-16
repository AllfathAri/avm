//
// Created by allfathari on 6/12/19.
//

#include "vm.h"
#include "instructions.h"
#include <stdlib.h>
#include <stdbool.h>

VM *vm_new() {
    VM *vm = malloc(sizeof(VM));
    vm->stack = int_stack_new();
    return vm;
}

void vm_delete(VM *vm) {
    free(vm->program);
    int_stack_delete(vm->stack);
    free(vm);
}

void vm_run(VM *vm) {
    while (true) {
        if (vm->pc >= vm->program_len) {
            break;
        }
        Opcode opcode = vm_decode_opcode(vm);
        vm_dispatch_opcode(vm, opcode);
    }
}

Opcode vm_decode_opcode(VM *vm) {
    Opcode opCode = opcode_from_u8(vm->program[vm->pc]);
    ++vm->pc;
    return opCode;
}

void vm_dispatch_LOAD(VM *vm) {
    u_int8_t reg = vm_next_8_bits(vm);
    u_int16_t number = vm_next_16_bits(vm);
    vm->registers[reg] = number;
}

#define VM_DISPATCH_BOP(vm, op) u_int8_t reg1 = vm_next_8_bits(vm); u_int8_t reg2 = vm_next_8_bits(vm); u_int8_t reg3 = vm_next_8_bits(vm); vm->registers[reg3] = vm->registers[reg1] op vm->registers[reg2];

void vm_dispatch_ADD(VM *vm) {
    VM_DISPATCH_BOP(vm, +)
}

void vm_dispatch_SUB(VM *vm) {
    VM_DISPATCH_BOP(vm, -)
}

void vm_dispatch_MUL(VM *vm) {
    VM_DISPATCH_BOP(vm, *)
}

void vm_dispatch_DIV(VM *vm) {
    VM_DISPATCH_BOP(vm, /)
    vm->remainder = reg1 % reg2;
}

#undef VM_DISPATCH_BOP

void vm_dispatch_HLT(VM *vm) {
    // TODO: halt mechanism
}


#define VM_DISPATCH_JMP(vm, f) u_int8_t reg = vm_next_8_bits(vm); u_int64_t target = vm->registers[reg]; vm->pc f target;

void vm_dispatch_JMP(VM *vm) {
    VM_DISPATCH_JMP(vm, =)
}

void vm_dispatch_JMPF(VM *vm) {
    VM_DISPATCH_JMP(vm, +=)
}

void vm_dispatch_JMPB(VM *vm) {
    VM_DISPATCH_JMP(vm, -=)
}

#undef VM_DISPATCH_JMP

#define VM_DISPATCH_EQ(vm, op) u_int8_t reg1 = vm_next_8_bits(vm); u_int8_t reg2 = vm_next_8_bits(vm); vm->equal_flag = vm->registers[reg1] op vm->registers[reg2]; vm_next_8_bits(vm);

void vm_dispatch_EQ(VM *vm) {
    VM_DISPATCH_EQ(vm, =)
}

void vm_dispatch_NEQ(VM *vm) {
    VM_DISPATCH_EQ(vm, !=)
}

void vm_dispatch_GTE(VM *vm) {
    VM_DISPATCH_EQ(vm, >=)
}

void vm_dispatch_LTE(VM *vm) {
    VM_DISPATCH_EQ(vm, <=)
}

void vm_dispatch_LT(VM *vm) {
    VM_DISPATCH_EQ(vm, <)
}

void vm_dispatch_GT(VM *vm) {
    VM_DISPATCH_EQ(vm, >)
}

#undef VM_DISPATCH_EQ

void vm_dispatch_JMPE(VM *vm) {
    if (vm->equal_flag) {
        u_int8_t reg = vm_next_8_bits(vm);
        u_int32_t target = vm->registers[reg];
        vm->pc = target;
    } else {
        // TODO: fix the bits
    }
}

void vm_dispatch_NOP(VM *vm) {
    vm_next_8_bits(vm);
    vm_next_8_bits(vm);
    vm_next_8_bits(vm);
}

void vm_dispatch_ALOC(VM *vm) {
    // TODO: implement heap
}

void vm_dispatch_INC(VM *vm) {
    u_int8_t reg = vm_next_8_bits(vm);
    ++vm->registers[reg];
    vm_next_8_bits(vm);
    vm_next_8_bits(vm);
}

void vm_dispatch_DEC(VM *vm) {
    u_int8_t reg = vm_next_8_bits(vm);
    --vm->registers[reg];
    vm_next_8_bits(vm);
    vm_next_8_bits(vm);
}

void vm_dispatch_DJMPE(VM *vm) {
    u_int16_t destination = vm_next_16_bits(vm);
    if (vm->equal_flag) {
        vm->pc = destination;
    } else {
        vm_next_8_bits(vm);
    }
}

void vm_dispatch_PRTS(VM *vm) {
    // TODO: implement printing
}

void vm_dispatch_LOADF64(VM *vm) {
    u_int8_t reg = vm_next_8_bits(vm);
    u_int16_t number = vm_next_16_bits(vm);
    vm->float_registers[reg] = number;
}

#define VM_DISPATCH_F64BOP(vm, op) u_int8_t reg1 = vm_next_8_bits(vm); u_int8_t reg2 = vm_next_8_bits(vm); u_int8_t reg3 = vm_next_8_bits(vm); vm->float_registers[reg3] = vm->float_registers[reg1] op vm->float_registers[reg2];

void vm_dispatch_ADDF64(VM *vm) {
    VM_DISPATCH_F64BOP(vm, +)
}

void vm_dispatch_SUBF64(VM *vm) {
    VM_DISPATCH_F64BOP(vm, -)
}

void vm_dispatch_MULF64(VM *vm) {
    VM_DISPATCH_F64BOP(vm, *)
}

void vm_dispatch_DIVF64(VM *vm) {
    VM_DISPATCH_F64BOP(vm, /)
}

#undef VM_DISPATCH_F64BOP

#define VM_DISPATCH_F64EQ(vm, op) u_int8_t reg1 = vm_next_8_bits(vm); u_int8_t reg2 = vm_next_8_bits(vm); vm->equal_flag = vm->float_registers[reg1] op vm->float_registers[reg2]; vm_next_8_bits(vm);

void vm_dispatch_EQF64(VM *vm) {
    VM_DISPATCH_F64EQ(vm, =)
}

void vm_dispatch_NEQF64(VM *vm) {
    VM_DISPATCH_F64EQ(vm, !=)
}

void vm_dispatch_GTF64(VM *vm) {
    VM_DISPATCH_F64EQ(vm, >)
}

void vm_dispatch_GTEF64(VM *vm) {
    VM_DISPATCH_F64EQ(vm, >=)
}

void vm_dispatch_LTF64(VM *vm) {
    VM_DISPATCH_F64EQ(vm, <)
}

void vm_dispatch_LTEF64(VM *vm) {
    VM_DISPATCH_F64EQ(vm, <=)
}

#undef VM_DISPATCH_F64BOP

void vm_dispatch_SHL(VM *vm) {
    // TODO: implement shifting
}

void vm_dispatch_SHR(VM *vm) {
    // TODO: implement shifting
}

#define VM_DISPATCH_BWOP(vm, op) u_int8_t reg1 = vm_next_8_bits(vm); u_int8_t reg2 = vm_next_8_bits(vm); u_int8_t reg3 = vm_next_8_bits(vm); vm->registers[reg3] = (unsigned) vm->registers[reg1] op (unsigned) vm->registers[reg2];

void vm_dispatch_AND(VM *vm) {
   VM_DISPATCH_BWOP(vm, &)
}

void vm_dispatch_OR(VM *vm) {
    VM_DISPATCH_BWOP(vm, |)
}

void vm_dispatch_XOR(VM *vm) {
    VM_DISPATCH_BWOP(vm, ^)
}

#undef VM_DISPATCH_BWOP

void vm_dispatch_NOT(VM *vm) {
    u_int8_t reg1 = vm_next_8_bits(vm);
    u_int8_t reg2 = vm_next_8_bits(vm);
    vm->registers[reg2] = !vm->registers[reg1];
    vm_next_8_bits(vm);
}

void vm_dispatch_LUI(VM *vm) {
    // TODO: implement shifting
}

void vm_dispatch_CLOOP(VM *vm) {
    u_int16_t loop_count = vm_next_16_bits(vm);
    vm->loop_counter = loop_count;
    vm_next_8_bits(vm);
}

void vm_dispatch_LOOP(VM *vm) {
    if (vm->loop_counter != 0) {
        --vm->loop_counter;
        u_int16_t target = vm_next_16_bits(vm);
        vm->pc = target;
    } else {
        vm->pc += 3;
    }
}

void vm_dispatch_LOADM(VM *vm) {
    // TODO: implement heap
}

void vm_dispatch_SETM(VM *vm) {
    // TODO: implement heap
}

void vm_dispatch_PUSH(VM *vm) {
    u_int8_t reg = vm_next_8_bits(vm);
    int32_t data = vm->registers[reg];
    int_stack_push(vm->stack, data);
    ++vm->sp;
    // TODO: shouldn't it use stack top?
}


void vm_dispatch_POP(VM *vm) {
    u_int8_t  reg = vm_next_8_bits(vm);
    int data = int_stack_pop(vm->stack);
    vm->registers[reg] = data;
}

void vm_dispatch_CALL(VM *vm) {
    size_t return_destination = vm->pc + 3;
    size_t destination = vm_next_16_bits(vm);
    int_stack_push(vm->stack, return_destination);
    int_stack_push(vm->stack, vm->bp);
    vm->bp = vm->sp;
    vm->pc = destination;
}

void vm_dispatch_RET(VM *vm) {
    vm->sp = vm->bp;
    vm->bp = int_stack_pop(vm->stack);
    vm->pc = int_stack_pop(vm->stack);
}

void vm_dispatch_IGL(VM *vm) {
    // TODO: Illegal mechanism
    vm->pc = vm->program_len;
}

// TODO: make sure index matches position in Opcode enum by tests


typedef void (*OpcodeDispatcher)(VM *);

static OpcodeDispatcher opcode_dispatchers[OPCODE_COUNT + 1] = {
        &vm_dispatch_LOAD,
        &vm_dispatch_ADD,
        &vm_dispatch_SUB,
        &vm_dispatch_MUL,
        &vm_dispatch_DIV,
        &vm_dispatch_HLT,
        &vm_dispatch_JMP,
        &vm_dispatch_JMPF,
        &vm_dispatch_JMPB,
        &vm_dispatch_EQ,
        &vm_dispatch_NEQ,
        &vm_dispatch_GTE,
        &vm_dispatch_LTE,
        &vm_dispatch_LT,
        &vm_dispatch_GT,
        &vm_dispatch_JMPE,
        &vm_dispatch_NOP,
        &vm_dispatch_ALOC,
        &vm_dispatch_INC,
        &vm_dispatch_DEC,
        &vm_dispatch_DJMPE,
        &vm_dispatch_PRTS,
        &vm_dispatch_LOADF64,
        &vm_dispatch_ADDF64,
        &vm_dispatch_SUBF64,
        &vm_dispatch_MULF64,
        &vm_dispatch_DIVF64,
        &vm_dispatch_EQF64,
        &vm_dispatch_NEQF64,
        &vm_dispatch_GTF64,
        &vm_dispatch_GTEF64,
        &vm_dispatch_LTF64,
        &vm_dispatch_LTEF64,
        &vm_dispatch_SHL,
        &vm_dispatch_SHR,
        &vm_dispatch_AND,
        &vm_dispatch_OR,
        &vm_dispatch_XOR,
        &vm_dispatch_NOT,
        &vm_dispatch_LUI,
        &vm_dispatch_CLOOP,
        &vm_dispatch_LOOP,
        &vm_dispatch_LOADM,
        &vm_dispatch_SETM,
        &vm_dispatch_PUSH,
        &vm_dispatch_POP,
        &vm_dispatch_CALL,
        &vm_dispatch_RET,
        &vm_dispatch_IGL
};

void vm_dispatch_opcode(VM *vm, Opcode opcode) {
    opcode_dispatchers[opcode](vm);
}

u_int8_t vm_next_8_bits(VM *vm) {
    u_int8_t result = vm->program[vm->pc];
    ++vm->pc;
    return result;
}

u_int8_t vm_next_16_bits(VM *vm) {
    u_int16_t head = vm->program[vm->pc] << 8u;
    ++vm->pc;
    u_int16_t tail = vm->program[vm->pc];
    ++vm->pc;
    u_int16_t result = head | tail;
    return result;
}