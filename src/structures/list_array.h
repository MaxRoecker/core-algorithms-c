#ifndef LIST_ARRAY_H
#define LIST_ARRAY_H
#include <math.h>
#include "array.h"

typedef struct {Array _array; size_t _begin; size_t _end;} ListArrayStruct;

typedef ListArrayStruct * ListArray;


ListArray listarray_create();

ListArray listarray_create_of(Array initial_state);

ListArray listarray_create_with(size_t length);

void listarray_destroy(ListArray *list);

size_t listarray_lenght(ListArray list);

unsigned char listarray_empty(ListArray list);

Array listarray_as_array(ListArray list);


void * listarray_get(ListArray list, size_t index);

size_t listarray_index_of(ListArray list, void *value);


void listarray_insert(ListArray list, size_t index, void *value);

void listarray_insert_right(ListArray list, size_t index, void *value);

void listarray_insert_left(ListArray list, size_t index, void *value);


void * listarray_remove(ListArray list, size_t index);

void * listarray_remove_right(ListArray list, size_t index);

void * listarray_remove_left(ListArray list, size_t index);


size_t listarray_max(ListArray list, ComparisonFunction comparison);

size_t listarray_min(ListArray list, ComparisonFunction comparison);


unsigned char _listarray_full(ListArray list);

void _listarray_resize(ListArray list, double factor);


// ListArray listarray_concat(ListArray one, ListArray another);
//
// ListArray listarray_union(ListArray one, ListArray another);
//
// ListArray listarray_difference(ListArray one, ListArray another);
//
//


#endif
