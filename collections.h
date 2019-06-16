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

Int_Stack *int_stack_new(void);

Int_Stack *int_stack_new_with_capacity(int);

int int_stack_size(Int_Stack *);

bool int_stack_is_empty(Int_Stack *);

bool int_stack_is_full(Int_Stack *);

void int_stack_push(Int_Stack *, int);

int int_stack_peek(Int_Stack *);

int int_stack_pop(Int_Stack *);

void int_stack_delete(Int_Stack *);

#endif //AVM_COLLECTIONS_H
