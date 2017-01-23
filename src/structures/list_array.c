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
ListArray listarray_create_of(Array initial_state) {
  ListArray list = listarray_create_with(array_lenght(initial_state));
  for (size_t i = 0; i < array_lenght(initial_state); i += 1) {
    void *value = array_get(initial_state, i);
    array_set(list->_array, i, value);
  }
  list->_begin = 0;
  list->_end = array_lenght(initial_state);
  return list;
}

/**
 * Creates an empty ListArray with the given size.
 */
ListArray listarray_create_with(size_t length) {
  Array array = array_create_empty(length + 1);
  ListArray list = ((ListArray) memory_alloc(sizeof(ListArrayStruct)));
  list->_array = array;
  list->_begin = length / 2;
  list->_end = length / 2;
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
 * Returns an array representation of the list.
 */
Array listarray_as_array(ListArray list) {
  Array array = array_slice(list->_array, list->_begin, list->_end);
  return array;
}

/**
 * Returns the value of the given index.
 */
void * listarray_get(ListArray list, size_t index) {
  if (index >= listarray_lenght(list)) {
    fprintf(stderr, "Index '%lu' out of bounds of the list.\n", index);
    exit(EXIT_FAILURE);
  }
  size_t real_index = (list->_begin + index) % array_lenght(list->_array);
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

/**
 * Inserts a value on a given index.
 */
void listarray_insert(ListArray list, size_t index, void *value) {
  if (_listarray_full(list)) {
    _listarray_resize(list, 1.5);
  }
  if (index > (listarray_lenght(list) / 2)) {
    listarray_insert_right(list, index, value);
  } else {
    listarray_insert_left(list, index, value);
  }
}

/**
 * Inserts a value on a given index by right.
 */
void listarray_insert_right(ListArray list, size_t index, void *value) {
  list->_end = (list->_end + 1) % array_lenght(list->_array);
  size_t real_index = (list->_begin + index) % array_lenght(list->_array);
  size_t i = list->_end;
  while (i != real_index) {
    size_t j = (i != 0)? (i - 1) : array_lenght(list->_array) - 1;
    void *list_value = array_get(list->_array, j);
    array_set(list->_array, i, list_value);
    i = (i != 0)? (i - 1) : array_lenght(list->_array) - 1;
  }
  array_set(list->_array, real_index, value);
}

/**
 * Inserts a value on a given index by left.
 */
void listarray_insert_left(ListArray list, size_t index, void *value) {
  list->_begin = (list->_begin != 0)?
    list->_begin - 1 : array_lenght(list->_array) - 1;
  size_t real_index = (list->_begin + index) % array_lenght(list->_array);
  size_t i = list->_begin;
  while (i != real_index) {
    size_t j = (i + 1) % array_lenght(list->_array);
    void *list_value = array_get(list->_array, j);
    array_set(list->_array, i, list_value);
    i = (i + 1) % array_lenght(list->_array);
  }
  array_set(list->_array, real_index, value);
}

/**
 * Remove a item of a list at the given index.
 */
void * listarray_remove(ListArray list, size_t index) {
  void *removed_value;
  if (index > (listarray_lenght(list) / 2)) {
    removed_value = listarray_remove_right(list, index);
  } else {
    removed_value = listarray_remove_left(list, index);
  }
  return removed_value;
}

/**
 * Remove a item of a list at the given index from the right.
 */
void * listarray_remove_right(ListArray list, size_t index) {
  size_t real_index = (list->_begin + index) % array_lenght(list->_array);
  void *removed_value = array_get(list->_array, real_index);
  size_t i = real_index;
  while (i != list->_end) {
    size_t j = (i + 1) % array_lenght(list->_array);
    void *list_value = array_get(list->_array, j);
    array_set(list->_array, i, list_value);
    i = (i + 1) % array_lenght(list->_array);
  }
  list->_end = (list->_end != 0)?
    list->_end - 1 : array_lenght(list->_array) - 1;
  return removed_value;
}

/**
 * Remove a item of a list at the given index from the left.
 */
void * listarray_remove_left(ListArray list, size_t index) {
  size_t real_index = (list->_begin + index) % array_lenght(list->_array);
  void *removed_value = array_get(list->_array, real_index);
  size_t i = real_index;
  while (i != list->_begin) {
    size_t j = (i != 0)? (i - 1) : array_lenght(list->_array) - 1;
    void *list_value = array_get(list->_array, j);
    array_set(list->_array, i, list_value);
    i = (i != 0)? (i - 1) : array_lenght(list->_array) - 1;
  }
  list->_begin = (list->_begin + 1) % array_lenght(list->_array);
  return removed_value;
}

/**
 * Returns the index of the maximum element based on given comparison.
 */
size_t listarray_max(ListArray list, ComparisonFunction comparison) {
  size_t max = 0;
  void *max_value = listarray_get(list, max);
  for (size_t i = 1; i < listarray_lenght(list); i += 1) {
    void *value = listarray_get(list, i);
    if (comparison(value, max_value) > 0) {
      max_value = value;
      max = i;
    }
  }
  return max;
}

/**
 * Returns the index of the minimum element based on given comparison.
 */
size_t listarray_min(ListArray list, ComparisonFunction comparison) {
  size_t min = 0;
  void *min_value = listarray_get(list, min);
  for (size_t i = 1; i < listarray_lenght(list); i += 1) {
    void *value = listarray_get(list, i);
    if (comparison(value, min_value) < 0) {
      min_value = value;
      min = i;
    }
  }
  return min;
}

/**
 * Returns 1 if the list's array is full, 0 otherwise.
 */
unsigned char _listarray_full(ListArray list) {
  return ((list->_end + 1) % array_lenght(list->_array)) == list->_begin;
}

/**
 * Resize the given list based on a factor.
 */
void _listarray_resize(ListArray list, double factor) {
  Array current_array = list->_array;
  size_t current_lenght = array_lenght(current_array);
  size_t resized_lenght = ((size_t) ((int) ceil(factor * current_lenght)));
  Array resized_array = array_create_empty(resized_lenght);
  size_t resized_begin = (current_lenght / 2);
  size_t resized_end = resized_begin + listarray_lenght(list);
  for (size_t i = 0; i < listarray_lenght(list); i += 1) {
    void *value = listarray_get(list, i);
    array_set(resized_array, resized_begin + i, value);
  }
  list->_array = resized_array;
  list->_begin = resized_begin;
  list->_end = resized_end;
  array_destroy(&current_array);
}
