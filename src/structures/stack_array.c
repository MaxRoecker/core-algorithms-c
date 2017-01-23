#include "stack_array.h"

/**
 * Creates an empty stack.
 * Time complexity: O(1)
 */
StackArray stackarray_create() {
  ListArray list = listarray_create();
  StackArray stack = ((StackArray) memory_alloc(sizeof(StackArrayStruct)));
  stack->_list = list;
  return stack;
}

/**
 * Creates a stack with a initial state.
 * Time complexity: O(n)
 */
StackArray stackarray_create_of(Array initial_state) {
  ListArray list = listarray_create_of(initial_state);
  StackArray stack = ((StackArray) memory_alloc(sizeof(StackArrayStruct)));
  stack->_list = list;
  return stack;
}

/**
 * Destroys the stack, freeing memory.
 * Time complexity: O(1)
 */
void stackarray_destroy(StackArray *stack) {
  listarray_destroy(&((*stack)->_list));
  free(*stack);
  *stack = NULL;
}

/**
 * Returns the stack current length.
 * Time complexity: O(1)
 */
size_t stackarray_lenght(StackArray stack) {
  return listarray_lenght(stack->_list);
}

/**
 * Returns 1 if there is no element in the stack; 0 otherwise.
 * Time complexity: O(1)
 */
unsigned char stackarray_empty(StackArray stack) {
  return listarray_empty(stack->_list);
}

/**
 * Return an array representation of the current state of the stack.
 * Time complexity: O(n)
 */
Array stackarray_as_array(StackArray stack) {
  return listarray_as_array(stack->_list);
}

/**
 * Push a value in the stack.
 * Time complexity:
 *  - Best case: O(1);
 *  - Average case: O(1);
 *  - Worst case: O(n).
 */
void stackarray_push(StackArray stack, void *value) {
  listarray_insert(stack->_list, 0, value);
}

/**
 * Pop a value from the stack.
 * Time complexity:
 *  - Best case: O(1);
 *  - Average case: O(1);
 *  - Worst case: O(1).
 */
void * stackarray_pop(StackArray stack) {
  return listarray_remove(stack->_list, 0);
}
