#ifndef HEAP_H
#define HEAP_H
#include "array.h"


size_t heap_parent(size_t index);

size_t heap_left(size_t index);

size_t heap_right(size_t index);

unsigned char heap_check(Array array, ComparisonFunction comparison);

void heap_build(Array array, ComparisonFunction comparison);

void heap_heapify(
    Array array, size_t index, size_t until, ComparisonFunction comparison);

#endif
