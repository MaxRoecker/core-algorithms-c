#ifndef ARRAY_H
#define ARRAY_H
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "../commons/memory.h"
#include "../commons/comparison.h"

typedef struct {void **_elements; size_t _length;} ArrayStruct;

typedef ArrayStruct * Array;


Array array_create_empty(size_t length);

Array array_create_from(void **elements, size_t length);

void array_destroy(Array *array);

size_t array_lenght(Array array);

void *array_get(Array array, size_t index);

void *array_set(Array array, size_t index, void *value);

unsigned char array_equals(Array one, Array another);

unsigned char array_same(Array one, Array another);

Array array_slice(Array array, size_t begin, size_t end);

Array array_concat(Array arrays);

Array array_merge(Array one, Array another, ComparisonFunction comparison);

void array_merge_into(
    Array array, size_t begin, size_t mid, size_t end,
    ComparisonFunction comparison);

void array_copy(
    Array source, Array target, size_t from, size_t until, size_t at);

Array array_clone(Array array);

Array _array_create(size_t length);

#endif
