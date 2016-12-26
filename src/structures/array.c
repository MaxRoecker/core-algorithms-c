#include "array.h"

Array array_create_empty(size_t length) {
  void **elements = _memory_alloc_elements(length);
  for (size_t i = 0; i < length; i++) {
    elements[i] = NULL;
  }
  Array array = {._elements = elements, .length = length};
  return array;
}


Array array_create_from(void **elements, size_t length) {
  void **internal_elements = _memory_alloc_elements(length);
  for (size_t i = 0; i < length; i++) {
    internal_elements[i] = elements[i];
  }
  Array array = {._elements = elements, .length = length};
  return array;
}


void * array_get(Array *array, size_t index) {
  if (index > array->length) {
    fprintf(
      stderr, "Index %lu out of bounds %lu to get.\n", index, array->length);
    exit(EXIT_FAILURE);
  }
  return array->_elements[index];
}


void * array_set(Array *array, size_t index, void *value) {
  if (index > array->length) {
    fprintf(
      stderr, "Index %lu out of bounds %lu to set.\n", index, array->length);
    exit(EXIT_FAILURE);
  }
  void *removed_value = array->_elements[index];
  array->_elements[index] = value;
  return removed_value;
}


int array_equals(Array *one, Array *another) {
  int equality = 0;
  if (one->length == another->length) {
    size_t index = 0;
    void *one_key = array_get(one, index);
    void *another_key = array_get(another, index);
    while ((one_key == another_key) && (index < one->length)) {
      index++;
      one_key = array_get(one, index);
      another_key = array_get(another, index);
    }
    if (index >= one->length) {
      equality = 1;
    }
  }
  return equality;
}


void * _memory_alloc_elements(size_t length) {
  return (void *) memory_alloc(sizeof(void *) * length);
}


int _is_index_out_of_bounds(Array *array, size_t index) {
  return index > array->length;
}
