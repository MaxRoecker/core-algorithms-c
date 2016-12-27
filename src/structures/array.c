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


Array array_slice(Array *array, size_t begin, size_t end) {
  if ((begin > end) || (begin > array->length) || (end > array->length)) {
    fprintf(stderr, "Begin or End value out of bounds.\n");
    exit(EXIT_FAILURE);
  }
  Array slice = array_create_empty(end - begin);
  for (size_t i = 0; i < slice.length; i++) {
    void * slice_value = array_get(array, i + begin);
    array_set(&slice, i, slice_value);
  }
  return slice;
}

Array array_merge(Array *one, Array *another, basic_comparison comparison) {
  Array merged_array = array_create_empty(one->length + another->length);
  size_t one_index = 0;
  size_t another_index = 0;
  size_t merge_index = 0;
  while ((one_index < one->length) && (another_index < another->length)) {
    void *one_value = array_get(one, one_index);
    void *another_value = array_get(another, another_index);
    if (comparison(one_value, another_value) > 0) {
      array_set(&merged_array, merge_index, another_value);
      another_index += 1;
    } else {
      array_set(&merged_array, merge_index, one_value);
      one_index += 1;
    }
    merge_index += 1;
  }
  while (one_index < one->length) {
    void *one_value = array_get(one, one_index);
    array_set(&merged_array, merge_index, one_value);
    merge_index += 1;
    one_index += 1;
  }
  while (another_index < another->length) {
    void *another_value = array_get(another, another_index);
    array_set(&merged_array, merge_index, another_value);
    merge_index += 1;
    another_index += 1;
  }
  return merged_array;
}


void * _memory_alloc_elements(size_t length) {
  return (void *) memory_alloc(sizeof(void *) * length);
}


int _is_index_out_of_bounds(Array *array, size_t index) {
  return index > array->length;
}
