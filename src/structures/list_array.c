#include "list_array.h"

/**
 * Creates an empty ListArray with standard size.
 */
ListArray listarray_create() {
  ListArray list = listarray_create_with(15);
  return list;
}

/**
 * Creates a ListArray with the elements and size of the given array.
 */
ListArray listarray_create_of(Array array) {
  ListArray list = listarray_create_with(array_lenght(array));
  for (size_t i = 0; i < array_lenght(array); i += 1) {
    void *value = array_get(array, i);
    array_set(list->_array, i, value);
  }
  list->_begin = 0;
  list->_end = array_lenght(array);
  return list;
}

/**
 * Creates an empty ListArray with the given size.
 */
ListArray listarray_create_with(size_t length) {
  Array array = array_create_empty(length + 1);
  ListArray list = ((ListArray) memory_alloc(sizeof(ListArrayStruct)));
  list->_array = array;
  list->_begin = 0;
  list->_end = 0;
  return list;
}

/**
 * Destroys the ListArray, freeing memory.
 */
void listarray_destroy(ListArray *list) {
  array_destroy(&((*list)->_array));
  free(*list);
  *list = NULL;
}

/**
 * Returns the length of the given list.
 */
size_t listarray_lenght(ListArray list) {
  size_t length = 0;
  if (list->_end > list->_begin) {
    length = list->_end - list->_begin;
  } else if (list->_end < list->_begin) {
    length = (list->_end) + (array_lenght(list->_array) - list->_begin);
  }
  return length;
}

/**
 * Returns 1 if there is no element in list; 0 otherwise.
 */
unsigned char listarray_empty(ListArray list) {
  return (list->_begin == list->_end);
}

/**
 * Returns the value of the given index.
 */
void * listarray_get(ListArray list, size_t index) {
  if (index >= listarray_lenght(list)) {
    fprintf(stderr, "Index '%lu' out of bounds of the list.\n", index);
    exit(EXIT_FAILURE);
  }
  size_t real_index = _listarray_array_index(list, index);
  void *value = array_get(list->_array, real_index);
  return value;
}

/**
 * Returns the index of the value given or the lenght of list if not found.
 *
 * Two values are the same if they share the same memory address.
 */
size_t listarray_index_of(ListArray list, void *value) {
  size_t i = 0;
  while ((i != listarray_lenght(list)) && (value != listarray_get(list, i))) {
    i += 1;
  }
  return i;
}


void * listarray_insert(ListArray list, size_t index, void *value) {
  // TODO Check if the array is full.
  size_t real_index = _listarray_array_index(list, index);
  size_t i = list->_end;
  while (i != real_index) {
    void *list_value = array_get(list->_array, i - 1);
    array_set(list->_array, i, list_value);
    i = (i - 1) % array_lenght(list->_array);
  }
  array_set(list->_array, real_index, value);
  list->_end = (list->_end + 1) % array_lenght(list->_array);
}

void * listarray_enqueue(ListArray queue, void *value) {
  listarray_insert(queue, queue->_end, value);
}

void * listarray_push(ListArray stack, void *value) {
  listarray_insert(stack, stack->_end, value);
}

/**
 * Returns the real index in the array.
 */
size_t _listarray_array_index(ListArray list, size_t index) {
  size_t real_index = (list->_begin + index) % array_lenght(list->_array);
  return real_index;
}
