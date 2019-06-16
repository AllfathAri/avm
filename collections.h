//
// Created by allfathari on 6/16/19.
//

#ifndef AVM_COLLECTIONS_H
#define AVM_COLLECTIONS_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Int_Stack {
    int top;
    int *array;
    size_t array_len;
} Int_Stack;

void int_stack_init(Int_Stack *);

void int_stack_init_with_capacity(Int_Stack *, int);

int int_stack_size(Int_Stack *);

bool int_stack_is_empty(Int_Stack *);

bool int_stack_is_full(Int_Stack *);

void int_stack_push(Int_Stack *, int);

int int_stack_peek(Int_Stack *);

int int_stack_pop(Int_Stack *);

void int_stack_free(Int_Stack *);

typedef struct Byte_Vector {
    size_t total;
    u_int8_t *array;
    size_t array_len;
} Byte_Vector;

void byte_vector_init(Byte_Vector *);
void byte_vector_init_with_capacity(Byte_Vector *, size_t);
int byte_vector_size(Byte_Vector *vector);
void byte_vector_add(Byte_Vector *, u_int8_t);
void byte_vector_set(Byte_Vector *, size_t , u_int8_t);
u_int8_t byte_vector_get(Byte_Vector *, size_t);
void byte_vector_delete(Byte_Vector *, size_t);
void byte_vector_free(Byte_Vector *);

#endif //AVM_COLLECTIONS_H
