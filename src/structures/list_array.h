#ifndef QUEUE_ARRAY_H
#define QUEUE_ARRAY_H
#include "array.h"

typedef struct {Array _array; size_t _begin; size_t _end;} ListArrayStruct;

typedef ListArrayStruct * ListArray;


ListArray listarray_create();

ListArray listarray_create_of(Array array);

ListArray listarray_create_with(size_t length);

void listarray_destroy(ListArray *list);

size_t listarray_lenght(ListArray list);

unsigned char listarray_empty(ListArray list);


void * listarray_get(ListArray list, size_t index);

size_t listarray_index_of(ListArray list, void *value);


void listarray_insert(ListArray list, size_t index, void *value);

void listarray_insert_right(ListArray list, size_t index, void *value);

void listarray_insert_left(ListArray list, size_t index, void *value);


// void * listarray_remove(ListArray list, size_t index);

// void listarray_enqueue(ListArray queue, void *value);
//
// void listarray_push(ListArray stack, void *value);


// void * listarray_remove(ListArray list, size_t index);
//
// void * listarray_dequeue(ListArray queue, void *value);
//
// void * listarray_pop(ListArray stack, void *value);
//
//
// size_t listarray_max(ListArray list);
//
// size_t listarray_min(ListArray list);
//
//
// ListArray listarray_concat(ListArray one, ListArray another);
//
// ListArray listarray_union(ListArray one, ListArray another);
//
// ListArray listarray_difference(ListArray one, ListArray another);
//
//


#endif
