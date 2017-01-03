#include "node.h"

/**
 * Returns a node with an value's address and children's clone.
 */
Node node_create(void *value, Array children) {
  Array children_copy = array_clone(children);
  Node node = ((Node) memory_alloc(sizeof(NodeStruct)));
  node->_children = children_copy;
  node->_value = value;
  return node;
}

/**
 * Returns the address of the value of the node.
 */
void * node_value(Node node) {
  return node->_value;
}

/**
 * Returns the child of the given index
 *
 * Can return NULL if the node doesn't have a child.
 */
Node node_child(Node node, size_t index) {
  Node child = ((Node) array_get(node->_children, index));
  return child;
}

/**
 * Returns a clone of the children of the node.
 */
Array node_children(Node node) {
  return array_clone(node->_children);
}

/**
 * Returns 1 if the node are equals, false otherwise.
 */
unsigned char node_equals(Node one, Node another) {
  unsigned char equality = node_same(one, another);
  if (!equality) {
    equality = (one->_value == another->_value);
    if (equality) {
      equality = array_equals(one->_children, another->_children);
    }
  }
  return equality;
}

/**
 * Returns 1 if the two nodes are exactly the same.
 *
 * Two nodes are "the same" if they share the same memory address.
 */
unsigned char node_same(Node one, Node another) {
  unsigned char sameness = ((void *) one) == ((void *) another);
  return sameness;
}

/**
 * Destroys the node, freeing memory.
 */
void node_destroy(Node *node) {
  Array children = (*node)->_children;
  array_destroy(&children);
  free(*node);
  *node = NULL;
}

/**
 * Returns a clone of the given node.
 */
Node node_clone(Node node) {
  Node copy = node_create(node->_value, node->_children);
  return copy;
}
