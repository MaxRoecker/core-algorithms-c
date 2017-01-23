#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H
#include "list_array.h"

typedef struct {ListArray _list;} StackArrayStruct;

typedef StackArrayStruct * StackArray;


StackArray stackarray_create();

StackArray stackarray_create_of(Array initial_state);

void stackarray_destroy(StackArray *stack);

size_t stackarray_lenght(StackArray stack);

unsigned char stackarray_empty(StackArray stack);

Array stackarray_as_array(StackArray stack);


void stackarray_push(StackArray stack, void *value);

void * stackarray_pop(StackArray stack);


#endif
