//
// Created by allfathari on 6/16/19.
//

#include <string.h>

#include "collections.h"

void int_stack_init(Int_Stack *stack) {
    return int_stack_init_with_capacity(stack, 16);
}

void int_stack_init_with_capacity(Int_Stack *stack, int capacity) {
    if (capacity <= 0) {
        // TODO: implement error handling
    }

    stack->top = -1;
    stack->array_len = capacity;
    stack->array = (int *) malloc(sizeof(int) * capacity);
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
        if (stack->top + 1 == stack->array_len / 4) {
            int_stack_resize(stack, stack->array_len / 2);
        }
        return stack->array[stack->top--];
    }
}

void int_stack_free(Int_Stack *stack) {
    free(stack->array);
}

void byte_vector_init(Byte_Vector *vector) {
    byte_vector_init_with_capacity(vector, 16);
}

void byte_vector_init_with_capacity(Byte_Vector *vector, size_t capacity) {
    vector->total = 0;
    vector->array_len = capacity;
    vector->array = malloc(sizeof(u_int8_t) * capacity);
}

int byte_vector_size(Byte_Vector *vector) {
    return vector->total;
}

void byte_vector_resize(Byte_Vector * vector, size_t capacity) {
    vector->array = realloc(vector->array, sizeof(u_int8_t) * capacity);
    vector->array_len = capacity;
}

void byte_vector_add(Byte_Vector *vector, u_int8_t element) {
    if (vector->total == vector->array_len) {
        byte_vector_resize(vector, vector->array_len * 2);
    }
    vector->array[vector->total++] = element;
}

void byte_vector_set(Byte_Vector *vector, size_t index, u_int8_t element) {
    if (index < vector->total) {
        vector->array[index] = element;
    }
    // TODO : implement error handling

}

u_int8_t byte_vector_get(Byte_Vector *vector, size_t index) {
    if (index < vector->total) {
        return vector->array[index];
    }
    // TODO : implement error handling
}

void byte_vector_delete(Byte_Vector *vector, size_t index) {
    if (index < vector->total) {
        vector->array[index] = 0;

        memcpy(&vector[index], &vector[index + 1], vector->total - index);

        --vector->total;

        if (vector->total == vector->array_len / 4) {
            byte_vector_resize(vector, vector->array_len / 2);
        }
    }
    // TODO : implement error handling
}

void byte_vector_free(Byte_Vector *vector) {
    free(vector->array);
}
