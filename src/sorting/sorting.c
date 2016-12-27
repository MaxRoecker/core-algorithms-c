#include "sorting.h"

void insertion_sort(Array *array, ComparisonFunction comparison) {
  for (size_t i = 1; i < array->length; i++) {
    void *key = array_get(array, i);
    size_t j = i;
    while ((j > 0) && (comparison(array_get(array, j - 1), key))) {
      array_set(array, j, array_get(array, j - 1));
      j -= 1;
    }
    array_set(array, j, key);
  }
}
