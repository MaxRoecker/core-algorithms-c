#include "queue_array.h"

/**
 * Creates an empty queue.
 * Time complexity: O(1)
 */
QueueArray queuearray_create() {
  ListArray list = listarray_create();
  QueueArray queue = ((QueueArray) memory_alloc(sizeof(QueueArrayStruct)));
  queue->_list = list;
  return queue;
}

/**
 * Creates a queue with a initial state.
 * Time complexity: O(n)
 */
QueueArray queuearray_create_of(Array initial_state) {
  ListArray list = listarray_create_of(initial_state);
  QueueArray queue = ((QueueArray) memory_alloc(sizeof(QueueArrayStruct)));
  queue->_list = list;
  return queue;
}

/**
 * Destroys the queue, freeing memory.
 * Time complexity: O(1)
 */
void queuearray_destroy(QueueArray *queue) {
  listarray_destroy(&((*queue)->_list));
  free(*queue);
  *queue = NULL;
}

/**
 * Returns the queue current length.
 * Time complexity: O(1)
 */
size_t queuearray_lenght(QueueArray queue) {
  return listarray_lenght(queue->_list);
}

/**
 * Returns 1 if there is no element in the queue; 0 otherwise.
 * Time complexity: O(1)
 */
unsigned char queuearray_empty(QueueArray queue) {
  return listarray_empty(queue->_list);
}

/**
 * Return an array representation of the current state of the queue.
 * Time complexity: O(n)
 */
Array queuearray_as_array(QueueArray queue) {
  return listarray_as_array(queue->_list);
}

/**
 * Enqueue a value in the queue.
 * Time complexity:
 *  - Best case: O(1);
 *  - Average case: O(1);
 *  - Worst case: O(n).
 */
void queuearray_enqueue(QueueArray queue, void *value) {
  listarray_insert(queue->_list, 0, value);
}

/**
 * Dequeue a value from the queue.
 * Time complexity:
 *  - Best case: O(1);
 *  - Average case: O(1);
 *  - Worst case: O(1).
 */
void * queuearray_dequeue(QueueArray queue) {
  return listarray_remove(queue->_list, listarray_lenght(queue->_list) - 1);
}
