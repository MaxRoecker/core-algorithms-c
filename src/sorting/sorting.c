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
  Array sorted = array_copy(array);
  _merge_sort_into(sorted, 0, array_lenght(array), comparison);
  return sorted;
}

void _merge_sort_into(
    Array array, size_t begin, size_t end, ComparisonFunction comparison) {
  if ((end - begin) > 1) {
    size_t mid = (begin + end) / 2;
    _merge_sort_into(array, begin, mid, comparison);
    _merge_sort_into(array, mid, end, comparison);
    array_merge_into(array, begin, mid, end, comparison);
  }
}
