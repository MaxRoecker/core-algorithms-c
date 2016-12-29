#ifndef SORTING_H
#define SORTING_H
#include <stdlib.h>
#include <stdio.h>
#include "../structures/array.h"

Array insertion_sort(const Array array, ComparisonFunction comparison);

Array merge_sort(Array array, ComparisonFunction comparison);

void _merge_sort_into(
    Array array, size_t begin, size_t end, ComparisonFunction comparison) ;

#endif
