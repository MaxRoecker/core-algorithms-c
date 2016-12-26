#ifndef SORTING_H
#define SORTING_H
#include <stdlib.h>
#include <stdio.h>
#include "../structures/array.h"

void insertion_sort(Array *, int (*comparison)(void *, void *));

#endif
