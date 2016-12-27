#include "array.h"

Array array_create_empty(size_t length) {
  Array array = ((Array) memory_alloc(sizeof(ArrayStruct)));
  void **elements = ((void *) memory_alloc(sizeof(void *) * length));
  for (size_t array_lenght = 0; array_lenght < length; array_lenght += 1) {
    elements[array_lenght] = NULL;
  }
  array->_length = length;
  array->_elements = elements;
  return array;
}


Array array_create_from(void **elements, size_t length) {
  Array array = ((Array) memory_alloc(sizeof(ArrayStruct)));
  void **internal_elements = ((void *) memory_alloc(sizeof(void *) * length));
  for (size_t array_lenght = 0; array_lenght < length; array_lenght += 1) {
    internal_elements[array_lenght] = elements[array_lenght];
  }
  array->_length = length;
  array->_elements = internal_elements;
  return array;
}


void array_destroy(Array *array) {
  free((*array)->_elements);
  free(*array);
  *(array) = NULL;
}


size_t array_lenght(Array array) {
  return array->_length;
}


void *array_get(Array array, size_t index) {
  if (index > array->_length) {
    fprintf(
      stderr, "Index %lu out of bounds %lu to get.\n", index, array->_length);
    exit(EXIT_FAILURE);
  }
  return array->_elements[index];
}


void *array_set(Array array, size_t index, void *value) {
  if (index > array->_length) {
    fprintf(
      stderr, "Index %lu out of bounds %lu to set.\n", index, array->_length);
    exit(EXIT_FAILURE);
  }
  void *removed_value = array->_elements[index];
  array->_elements[index] = value;
  return removed_value;
}


unsigned char array_equals(Array one, Array another) {
  unsigned char equality = 0;
  if (array_lenght(one) == array_lenght(another)) {
    size_t index = 0;
    void *one_key = array_get(one, index);
    void *another_key = array_get(another, index);
    while ((one_key == another_key) && (index < array_lenght(one))) {
      index += 1;
      one_key = array_get(one, index);
      another_key = array_get(another, index);
    }
    if (index >= array_lenght(one)) {
      equality = 1;
    }
  }
  return equality;
}


Array array_slice(Array array, size_t begin, size_t end) {
  if (begin > end) {
    fprintf(stderr, "Invalid begin or end values.\n");
    exit(EXIT_FAILURE);
  }
  if ((begin > array_lenght(array)) || (end > array_lenght(array))) {
    fprintf(stderr, "Begin or end values out of array bounds.\n");
    exit(EXIT_FAILURE);
  }
  Array slice = array_create_empty(end - begin);
  for (size_t i = 0; i < array_lenght(slice); i += 1) {
    void *value = array_get(array, i + begin);
    array_set(slice, i, value);
  }
  return slice;
}


Array array_merge(Array one, Array another, ComparisonFunction comparison) {
  Array merged_array = array_create_empty(
      array_lenght(one) + array_lenght(another));
  size_t i = 0;
  size_t j = 0;
  size_t k = 0;
  while ((i < array_lenght(one)) && (j < array_lenght(another))) {
    void *a = array_get(one, i);
    void *b = array_get(another, j);
    if (comparison(a, b) > 0) {
      array_set(merged_array, k, b);
      j += 1;
    } else {
      array_set(merged_array, k, a);
      i += 1;
    }
    k += 1;
  }
  while (i < array_lenght(one)) {
    void *a = array_get(one, i);
    array_set(merged_array, k, a);
    k += 1;
    i += 1;
  }
  while (j < array_lenght(another)) {
    void *b = array_get(another, j);
    array_set(merged_array, k, b);
    k += 1;
    j += 1;
  }
  return merged_array;
}
