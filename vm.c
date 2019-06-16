//
// Created by allfathari on 6/12/19.
//

#include "vm.h"
#include "instructions.h"
#include <stdlib.h>
#include <stdbool.h>

const size_t DEFAULT_STACK_SPACE = 2097152;

void vm_init(VM *vm) {
    byte_vector_init(&vm->program);
    int_stack_init_with_capacity(&vm->stack, DEFAULT_STACK_SPACE);
}

void vm_free(VM *vm) {
    byte_vector_free(&vm->program);
    int_stack_free(&vm->stack);
}

void vm_run(VM *vm) {
    while (true) {
        if (vm->pc >= byte_vector_size(&vm->program)) {
            break;
        }
        Opcode opcode = vm_decode_opcode(vm);
        vm_execute_instruction(vm, opcode);
    }
}

Opcode vm_decode_opcode(VM *vm) {
    u_int8_t byte = byte_vector_get(&vm->program, vm->pc);
    Opcode opCode = opcode_from_u8(byte);
    ++vm->pc;
    return opCode;
}

void vm_execute_LOAD(VM *vm) {
    u_int8_t reg = vm_next_8_bits(vm);
    u_int16_t number = vm_next_16_bits(vm);
    vm->registers[reg] = number;
}

#define VM_EXECUTE_BOP(vm, op) u_int8_t reg1 = vm_next_8_bits(vm); u_int8_t reg2 = vm_next_8_bits(vm); u_int8_t reg3 = vm_next_8_bits(vm); vm->registers[reg3] = vm->registers[reg1] op vm->registers[reg2];

void vm_execute_ADD(VM *vm) {
    VM_EXECUTE_BOP(vm, +)
}

void vm_execute_SUB(VM *vm) {
    VM_EXECUTE_BOP(vm, -)
}

void vm_execute_MUL(VM *vm) {
    VM_EXECUTE_BOP(vm, *)
}

void vm_execute_DIV(VM *vm) {
    VM_EXECUTE_BOP(vm, /)
    vm->remainder = reg1 % reg2;
}

#undef VM_EXECUTE_BOP

void vm_execute_HLT(VM *vm) {
    // TODO: halt mechanism
}


#define VM_EXECUTE_JMP(vm, f) u_int8_t reg = vm_next_8_bits(vm); u_int64_t target = vm->registers[reg]; vm->pc f target;

void vm_execute_JMP(VM *vm) {
    VM_EXECUTE_JMP(vm, =)
}

void vm_execute_JMPF(VM *vm) {
    VM_EXECUTE_JMP(vm, +=)
}

void vm_execute_JMPB(VM *vm) {
    VM_EXECUTE_JMP(vm, -=)
}

#undef VM_EXECUTE_JMP

#define VM_EXECUTE_EQ(vm, op) u_int8_t reg1 = vm_next_8_bits(vm); u_int8_t reg2 = vm_next_8_bits(vm); vm->equal_flag = vm->registers[reg1] op vm->registers[reg2]; vm_next_8_bits(vm);

void vm_execute_EQ(VM *vm) {
    VM_EXECUTE_EQ(vm, =)
}

void vm_execute_NEQ(VM *vm) {
    VM_EXECUTE_EQ(vm, !=)
}

void vm_execute_GTE(VM *vm) {
    VM_EXECUTE_EQ(vm, >=)
}

void vm_execute_LTE(VM *vm) {
    VM_EXECUTE_EQ(vm, <=)
}

void vm_execute_LT(VM *vm) {
    VM_EXECUTE_EQ(vm, <)
}

void vm_execute_GT(VM *vm) {
    VM_EXECUTE_EQ(vm, >)
}

#undef VM_EXECUTE_EQ

void vm_execute_JMPE(VM *vm) {
    if (vm->equal_flag) {
        u_int8_t reg = vm_next_8_bits(vm);
        u_int32_t target = vm->registers[reg];
        vm->pc = target;
    } else {
        // TODO: fix the bits
    }
}

void vm_execute_NOP(VM *vm) {
    vm_next_8_bits(vm);
    vm_next_8_bits(vm);
    vm_next_8_bits(vm);
}

void vm_execute_ALOC(VM *vm) {
    // TODO: implement heap
}

void vm_execute_INC(VM *vm) {
    u_int8_t reg = vm_next_8_bits(vm);
    ++vm->registers[reg];
    vm_next_8_bits(vm);
    vm_next_8_bits(vm);
}

void vm_execute_DEC(VM *vm) {
    u_int8_t reg = vm_next_8_bits(vm);
    --vm->registers[reg];
    vm_next_8_bits(vm);
    vm_next_8_bits(vm);
}

void vm_execute_DJMPE(VM *vm) {
    u_int16_t destination = vm_next_16_bits(vm);
    if (vm->equal_flag) {
        vm->pc = destination;
    } else {
        vm_next_8_bits(vm);
    }
}

void vm_execute_PRTS(VM *vm) {
    // TODO: implement printing
}

void vm_execute_LOADF64(VM *vm) {
    u_int8_t reg = vm_next_8_bits(vm);
    u_int16_t number = vm_next_16_bits(vm);
    vm->float_registers[reg] = number;
}

#define VM_EXECUTE_F64BOP(vm, op) u_int8_t reg1 = vm_next_8_bits(vm); u_int8_t reg2 = vm_next_8_bits(vm); u_int8_t reg3 = vm_next_8_bits(vm); vm->float_registers[reg3] = vm->float_registers[reg1] op vm->float_registers[reg2];

void vm_execute_ADDF64(VM *vm) {
    VM_EXECUTE_F64BOP(vm, +)
}

void vm_execute_SUBF64(VM *vm) {
    VM_EXECUTE_F64BOP(vm, -)
}

void vm_execute_MULF64(VM *vm) {
    VM_EXECUTE_F64BOP(vm, *)
}

void vm_execute_DIVF64(VM *vm) {
    VM_EXECUTE_F64BOP(vm, /)
}

#undef VM_EXECUTE_F64BOP

#define VM_EXECUTE_F64EQ(vm, op) u_int8_t reg1 = vm_next_8_bits(vm); u_int8_t reg2 = vm_next_8_bits(vm); vm->equal_flag = vm->float_registers[reg1] op vm->float_registers[reg2]; vm_next_8_bits(vm);

void vm_execute_EQF64(VM *vm) {
    VM_EXECUTE_F64EQ(vm, =)
}

void vm_execute_NEQF64(VM *vm) {
    VM_EXECUTE_F64EQ(vm, !=)
}

void vm_execute_GTF64(VM *vm) {
    VM_EXECUTE_F64EQ(vm, >)
}

void vm_execute_GTEF64(VM *vm) {
    VM_EXECUTE_F64EQ(vm, >=)
}

void vm_execute_LTF64(VM *vm) {
    VM_EXECUTE_F64EQ(vm, <)
}

void vm_execute_LTEF64(VM *vm) {
    VM_EXECUTE_F64EQ(vm, <=)
}

#undef VM_EXECUTE_F64BOP

void vm_execute_SHL(VM *vm) {
    // TODO: implement shifting
}

void vm_execute_SHR(VM *vm) {
    // TODO: implement shifting
}

#define VM_EXECUTE_BWOP(vm, op) u_int8_t reg1 = vm_next_8_bits(vm); u_int8_t reg2 = vm_next_8_bits(vm); u_int8_t reg3 = vm_next_8_bits(vm); vm->registers[reg3] = (unsigned) vm->registers[reg1] op (unsigned) vm->registers[reg2];

void vm_execute_AND(VM *vm) {
   VM_EXECUTE_BWOP(vm, &)
}

void vm_execute_OR(VM *vm) {
    VM_EXECUTE_BWOP(vm, |)
}

void vm_execute_XOR(VM *vm) {
    VM_EXECUTE_BWOP(vm, ^)
}

#undef VM_EXECUTE_BWOP

void vm_execute_NOT(VM *vm) {
    u_int8_t reg1 = vm_next_8_bits(vm);
    u_int8_t reg2 = vm_next_8_bits(vm);
    vm->registers[reg2] = !vm->registers[reg1];
    vm_next_8_bits(vm);
}

void vm_execute_LUI(VM *vm) {
    // TODO: implement shifting
}

void vm_execute_CLOOP(VM *vm) {
    u_int16_t loop_count = vm_next_16_bits(vm);
    vm->loop_counter = loop_count;
    vm_next_8_bits(vm);
}

void vm_execute_LOOP(VM *vm) {
    if (vm->loop_counter != 0) {
        --vm->loop_counter;
        u_int16_t target = vm_next_16_bits(vm);
        vm->pc = target;
    } else {
        vm->pc += 3;
    }
}

void vm_execute_LOADM(VM *vm) {
    // TODO: implement heap
}

void vm_execute_SETM(VM *vm) {
    // TODO: implement heap
}

void vm_execute_PUSH(VM *vm) {
    u_int8_t reg = vm_next_8_bits(vm);
    int32_t data = vm->registers[reg];
    int_stack_push(&vm->stack, data);
    ++vm->sp;
    // TODO: shouldn't it use stack top?
}


void vm_execute_POP(VM *vm) {
    u_int8_t  reg = vm_next_8_bits(vm);
    int data = int_stack_pop(&vm->stack);
    vm->registers[reg] = data;
}

void vm_execute_CALL(VM *vm) {
    size_t return_destination = vm->pc + 3;
    size_t destination = vm_next_16_bits(vm);
    int_stack_push(&vm->stack, return_destination);
    int_stack_push(&vm->stack, vm->bp);
    vm->bp = vm->sp;
    vm->pc = destination;
}

void vm_execute_RET(VM *vm) {
    vm->sp = vm->bp;
    vm->bp = int_stack_pop(&vm->stack);
    vm->pc = int_stack_pop(&vm->stack);
}

void vm_execute_IGL(VM *vm) {
    // TODO: Illegal mechanism
    vm->pc = byte_vector_size(&vm->program);
}

// TODO: make sure index matches position in Opcode enum by tests


typedef void (*InstructionExecuter)(VM *);

static InstructionExecuter opcode_executors[OPCODE_COUNT + 1] = {
        &vm_execute_LOAD,
        &vm_execute_ADD,
        &vm_execute_SUB,
        &vm_execute_MUL,
        &vm_execute_DIV,
        &vm_execute_HLT,
        &vm_execute_JMP,
        &vm_execute_JMPF,
        &vm_execute_JMPB,
        &vm_execute_EQ,
        &vm_execute_NEQ,
        &vm_execute_GTE,
        &vm_execute_LTE,
        &vm_execute_LT,
        &vm_execute_GT,
        &vm_execute_JMPE,
        &vm_execute_NOP,
        &vm_execute_ALOC,
        &vm_execute_INC,
        &vm_execute_DEC,
        &vm_execute_DJMPE,
        &vm_execute_PRTS,
        &vm_execute_LOADF64,
        &vm_execute_ADDF64,
        &vm_execute_SUBF64,
        &vm_execute_MULF64,
        &vm_execute_DIVF64,
        &vm_execute_EQF64,
        &vm_execute_NEQF64,
        &vm_execute_GTF64,
        &vm_execute_GTEF64,
        &vm_execute_LTF64,
        &vm_execute_LTEF64,
        &vm_execute_SHL,
        &vm_execute_SHR,
        &vm_execute_AND,
        &vm_execute_OR,
        &vm_execute_XOR,
        &vm_execute_NOT,
        &vm_execute_LUI,
        &vm_execute_CLOOP,
        &vm_execute_LOOP,
        &vm_execute_LOADM,
        &vm_execute_SETM,
        &vm_execute_PUSH,
        &vm_execute_POP,
        &vm_execute_CALL,
        &vm_execute_RET,
        &vm_execute_IGL
};

void vm_execute_instruction(VM *vm, Opcode opcode) {
    opcode_executors[opcode](vm);
}

u_int8_t vm_next_8_bits(VM *vm) {
    u_int8_t byte = byte_vector_get(&vm->program, vm->pc);
    u_int8_t result = byte;
    ++vm->pc;
    return result;
}

u_int8_t vm_next_16_bits(VM *vm) {
    u_int8_t byte1 = byte_vector_get(&vm->program, vm->pc);
    u_int16_t head = byte1 << 8u;
    ++vm->pc;

    u_int8_t byte2 = byte_vector_get(&vm->program, vm->pc);
    u_int16_t tail = byte2;
    ++vm->pc;

    u_int16_t result = head | tail;
    return result;
}