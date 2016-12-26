#ifndef ARRAY_H
#define ARRAY_H
#include <stdlib.h>
#include <stdio.h>
#include "../commons/memory.h"

typedef struct Array {
  void **elements;
  const size_t length;
} Array;

Array array_create_empty(size_t length);

Array array_create_from(void **elements, size_t length);

void * array_get(Array *array, size_t index);

void * array_set(Array *array, size_t index, void *value);

int array_equals(Array *one, Array *another);

void * _memory_alloc_elements(size_t length);

int _is_index_out_of_bounds(Array *array, size_t index);


// Array array_create(const element*, const unsigned long int);
//




#endif
