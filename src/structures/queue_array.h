#ifndef QUEUE_ARRAY_H
#define QUEUE_ARRAY_H
#include "list_array.h"

typedef struct {ListArray _list;} QueueArrayStruct;

typedef QueueArrayStruct * QueueArray;


QueueArray queuearray_create();

QueueArray queuearray_create_of(Array initial_state);

void queuearray_destroy(QueueArray *queue);

size_t queuearray_lenght(QueueArray queue);

unsigned char queuearray_empty(QueueArray queue);

Array queuearray_as_array(QueueArray queue);


void queuearray_enqueue(QueueArray queue, void *value);

void * queuearray_dequeue(QueueArray queue);


#endif
