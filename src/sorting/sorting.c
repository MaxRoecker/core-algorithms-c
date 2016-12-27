#include "sorting.h"

Array insertion_sort(const Array array, ComparisonFunction comparison) {
  Array sorted = array_copy(array);
  for (size_t i = 1; i < array_lenght(sorted); i += 1) {
    void *key = array_get(sorted, i);
    size_t j = i;
    while ((j > 0) && (comparison(array_get(sorted, j - 1), key))) {
      array_set(sorted, j, array_get(sorted, j - 1));
      j -= 1;
    }
    array_set(sorted, j, key);
  }
  return sorted;
}

Array merge_sort(Array array, ComparisonFunction comparison) {
  Array sorted;
  size_t length = array_lenght(array);
  if (length > 1) {
    size_t midpoint = length / 2;
    Array left = array_slice(array, 0, midpoint);
    Array right = array_slice(array, midpoint, length);
    Array left_sorted = merge_sort(left, comparison);
    array_destroy(&left);
    Array right_sorted = merge_sort(right, comparison);
    array_destroy(&right);
    sorted = array_merge(left_sorted, right_sorted, comparison);
    array_destroy(&left_sorted);
    array_destroy(&right_sorted);
  } else {
    sorted = array_copy(array);
  }
  return sorted;
}
