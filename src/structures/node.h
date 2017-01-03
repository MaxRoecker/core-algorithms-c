#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <stdio.h>
#include "array.h"

typedef struct {
  void *_value;
  Array _children;
} NodeStruct;

typedef NodeStruct * Node;


Node node_create(void *value, Array children);

void * node_value(Node node);

Node node_child(Node node, size_t index);

Array node_children(Node node);

unsigned char node_equals(Node one, Node another);

unsigned char node_same(Node one, Node another);

void node_destroy(Node *node);

Node node_clone(Node node);

#endif
