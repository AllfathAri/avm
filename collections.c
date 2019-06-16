//
// Created by allfathari on 6/16/19.
//

#include "collections.h"

Int_Stack *int_stack_new(void) {
    return int_stack_new_with_capacity(16);
}

Int_Stack *int_stack_new_with_capacity(int capacity) {
    if (capacity <= 0) {
        return NULL;
    }

    Int_Stack *stack = malloc(sizeof(Int_Stack));

    stack->top = -1;
    stack->array_len = capacity;
    stack->array = (int *) malloc(sizeof(int) * capacity);

    return stack;
}

int int_stack_size(Int_Stack *stack) {
    return stack->top + 1;
}

bool int_stack_is_empty(Int_Stack *stack) {
    return stack->top == -1;
}

bool int_stack_is_full(Int_Stack *stack) {
    return stack->top == stack->array_len - 1;
}

void int_stack_resize(Int_Stack *stack, int capacity) {
    stack->array = realloc(stack->array, sizeof(int) * capacity);
}

void int_stack_push(Int_Stack *stack, int element) {
    if (int_stack_is_full(stack)) {
        int_stack_resize(stack, stack->array_len * 2);
    }

    stack->array[++stack->top] = element;
}

int int_stack_peek(Int_Stack *stack) {
    if (int_stack_is_empty(stack)) {
        // TODO: implement error handling
    } else {
        return stack->array[stack->top];
    }
}

int int_stack_pop(Int_Stack *stack) {
    if (int_stack_is_empty(stack)) {
        // TOOD: implement error handling
    } else {
        if (stack->top <= stack->array_len / 4) {
            int_stack_resize(stack, stack->array_len / 2);
        }
        return stack->array[stack->top--];
    }
}

void int_stack_delete(Int_Stack *stack) {
    free(stack->array);
    free(stack);
}
