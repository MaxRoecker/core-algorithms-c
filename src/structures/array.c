#include "array.h"

/**
 * Create a array of NULL with the given lenght.
 */
Array array_create_empty(size_t length) {
  Array array = _array_create(length);
  for (size_t i = 0; i < length; i += 1) {
    array_set(array, i, NULL);
  }
  return array;
}

/**
 * Create a array of the given elements with the given lenght.
 */
Array array_create_from(void **elements, size_t length) {
  Array array = _array_create(length);
  for (size_t i = 0; i < length; i += 1) {
    array_set(array, i, elements[i]);
  }
  return array;
}

/**
 * Destroys the array, but not the content it points to; freeing memory.
 */
void array_destroy(Array *array) {
  free((*array)->_elements);
  free(*array);
  *(array) = NULL;
}

/**
 * Returns the length of the given array.
 */
size_t array_lenght(Array array) {
  return array->_length;
}

/**
 * Returns a pointer to indexed element.
 */
void *array_get(Array array, size_t index) {
  if (index > array->_length) {
    fprintf(
      stderr, "Index %lu out of bounds %lu to get.\n", index, array->_length);
    exit(EXIT_FAILURE);
  }
  return array->_elements[index];
}

/**
 * Put a pointer to an indexed element.
 */
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

/**
 * Returns 1 if the array is equal to another. 0 otherwise.
 *
 * An array is equal to another only if all its elements are equals, i.e.
 * all the elements points to the same address.
 */
unsigned char array_equals(Array one, Array another) {
  unsigned char equality = array_same(one, another);
  if (!equality) {
    equality = (array_lenght(one) == array_lenght(another));
    if (equality) {
      size_t index = 0;
      while ((index < array_lenght(one)) && (equality)) {
        equality = (array_get(one, index) == array_get(another, index));
        index += 1;
      }
    }
  }
  return equality;
}

/**
 * Returns 1 if the two arrays are exactly the same.
 *
 * Two arrays are "the same" if they share the same memory address.
 */
unsigned char array_same(Array one, Array another) {
  unsigned char sameness = (((void *) one) == ((void *) another));
  return sameness;
}

/**
 * Returns a new subarray limited by the begin (inclusive) and end (exclusive).
 */
Array array_slice(Array array, size_t begin, size_t end) {
  if (begin > end) {
    fprintf(stderr, "Invalid begin or end values.\n");
    exit(EXIT_FAILURE);
  }
  if ((begin > array_lenght(array)) || (end > array_lenght(array))) {
    fprintf(stderr, "Begin or end values out of array bounds.\n");
    exit(EXIT_FAILURE);
  }
  Array slice = _array_create(end - begin);
  for (size_t i = 0; i < array_lenght(slice); i += 1) {
    void *value = array_get(array, i + begin);
    array_set(slice, i, value);
  }
  return slice;
}

/**
 * Concatenates a Array of Arrays into a new one.
 */
Array array_concat(Array arrays) {
  size_t total_lenght = 0;
  for (size_t i = 0; i < array_lenght(arrays); i += 1) {
    Array array = *((Array *) array_get(arrays, i));
    total_lenght += array_lenght(array);
  }
  Array concat = _array_create(total_lenght);
  size_t k = 0;
  for (size_t i = 0; i < array_lenght(arrays); i += 1) {
    Array array = *((Array *) array_get(arrays, i));
    for (size_t j = 0; j < array_lenght(array); j += 1) {
      void *value = array_get(array, j);
      array_set(concat, k, value);
      k += 1;
    }
  }
  return concat;
}

/**
 * Merge two given arrays based on a comparison function.
 */
Array array_merge(Array one, Array another, ComparisonFunction comparison) {
  void *arrays_elements[] = {&one, &another};
  Array arrays = array_create_from(arrays_elements, 2);
  Array merged = array_concat(arrays);
  array_destroy(&arrays);
  size_t begin = 0,
         mid = array_lenght(one),
         end = array_lenght(merged);
  array_merge_into(merged, begin, mid, end, comparison);
  return merged;
}

/**
 * Merge two subarrays defined by begin, mid and end of an array.
 */
void array_merge_into(
    Array array, size_t begin, size_t mid, size_t end,
    ComparisonFunction comparison) {
  Array left = array_slice(array, begin, mid);
  Array right = array_slice(array, mid, end);
  size_t i = 0,
         j = 0,
         k = begin;
  while ((i < array_lenght(left)) && (j < array_lenght(right))) {
    void *left_value = array_get(left, i),
         *right_value = array_get(right, j);
    if (comparison(right_value, left_value) > 0) {
      array_set(array, k, left_value);
      i += 1;
    } else {
      array_set(array, k, right_value);
      j += 1;
    }
    k += 1;
  }
  while (i < array_lenght(left)) {
    void *value = array_get(left, i);
    array_set(array, k, value);
    k += 1;
    i += 1;
  }
  while (j < array_lenght(right)) {
    void *value = array_get(right, j);
    array_set(array, k, value);
    k += 1;
    j += 1;
  }
  array_destroy(&left);
  array_destroy(&right);
}

void array_copy(
    Array source, Array target, size_t from, size_t until, size_t at) {
  size_t lenght = until - from;
  for (size_t i = 0; i < lenght; i += 1) {
    void *value = array_get(source, from + i);
    array_set(target, at + i, value);
  }
}

/**
 * Return a copy of the array. Do not copies the content the array points to.
 */
Array array_clone(Array array) {
  Array copy = _array_create(array_lenght(array));
  for (size_t i = 0; i < array_lenght(array); i += 1) {
    void *value = array_get(array, i);
    array_set(copy, i, value);
  }
  return copy;
}

/**
 * Create a array with the given lenght, allocating memory.
 */
Array _array_create(size_t length) {
  Array array = ((Array) memory_alloc(sizeof(ArrayStruct)));
  void **elements = ((void *) memory_alloc(sizeof(void *) * length));
  array->_elements = elements;
  array->_length = length;
  return array;
}
