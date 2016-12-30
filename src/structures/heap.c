#include "heap.h"

/**
 * Returns the index of the parent of a given index.
 */
size_t heap_parent(size_t index) {
  size_t parent = 0;
  if (index > 0) {
    parent = (index - 1) / 2;
  }
  return parent;
}

/**
 * Returns the index of the left child of a given index.
 */
size_t heap_left(size_t index) {
  return 2 * index;
}

/**
 * Returns the index of the right child of the given index.
 */
size_t heap_right(size_t index) {
  return 2 * index + 1;
}

/**
 * Returns 1 if the array is a heap based on given comparison, 0 otherwise.
 */
unsigned char heap_check(Array array, ComparisonFunction comparison) {
  unsigned char has_heap_propertie = 1;
  if (array_lenght(array) > 1) {
    has_heap_propertie = 1;
    size_t i = 1;
    while ((i < array_lenght(array)) && (has_heap_propertie)) {
      void *current = array_get(array, i),
           *parent = array_get(array, heap_parent(i));
      if (comparison(parent, current) >= 0) {
        i += 1;
      } else {
        has_heap_propertie = 0;
      }
    }
  }
  return has_heap_propertie;
}

/**
 * Build a heap into the given array based on given comparison.
 */
void heap_build(Array array, ComparisonFunction comparison) {
  for (size_t i = array_lenght(array) / 2; i > 0; i -= 1) {
    heap_heapify(array, i, array_lenght(array), comparison);
  }
  heap_heapify(array, 0, array_lenght(array), comparison);
}

/**
 * Turns into a heap the index of a given array based on a given comparison.
 */
void heap_heapify(
    Array array, size_t index, size_t until, ComparisonFunction comparison) {
  if (until > index) {
    size_t left = heap_left(index),
           right = heap_right(index),
           largest = index;
    void *largest_value = array_get(array, largest);
    if (left < until) {
      void *left_value = array_get(array, left);
      if (comparison(left_value, largest_value) > 0) {
        largest = left;
        largest_value = left_value;
      }
    }
    if (right < until) {
      void *right_value = array_get(array, right);
      if (comparison(right_value, largest_value) > 0) {
        largest = right;
        largest_value = right_value;
      }
    }
    if (largest != index) {
      void *index_value = array_get(array, index);
      array_set(array, index, largest_value);
      array_set(array, largest, index_value);
      heap_heapify(array, largest, until, comparison);
    }
  }
}
