#include "sorting.h"

Array insertion_sort(const Array array, ComparisonFunction comparison) {
  Array copy = array_copy(array);
  for (size_t i = 1; i < array_lenght(copy); i += 1) {
    void *key = array_get(copy, i);
    size_t j = i;
    while ((j > 0) && (comparison(array_get(copy, j - 1), key))) {
      array_set(copy, j, array_get(copy, j - 1));
      j -= 1;
    }
    array_set(copy, j, key);
  }
  return copy;
}
