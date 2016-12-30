#include <stdio.h>
#include <tap.h>
#include "../src/structures/heap.h"

int zero = 0,
    one = 1,
    two = 2,
    three = 3,
    four = 4;

char compare_ascending_integers(void *const one, void *const another) {
  int one_value = *((int *) one);
  int another_value = *((int *) another);
  char comparison = 0;
  if (one_value < another_value) {
    comparison = -1;
  }
  if (one_value > another_value) {
    comparison = 1;
  }
  return comparison;
}

char compare_descending_integers(void *const one, void *const another) {
  int one_value = *((int *) one);
  int another_value = *((int *) another);
  char comparison = 0;
  if (one_value > another_value) {
    comparison = -1;
  }
  if (one_value < another_value) {
    comparison = 1;
  }
  return comparison;
}

void test_heap_basics() {
  // 10
  ComparisonFunction comparison_asc = &compare_ascending_integers;
  ComparisonFunction comparison_desc = &compare_descending_integers;
  void *max_heap_elements[] = {&four, &two, &three, &zero, &one};
  void *min_heap_elements[] = {&zero, &two, &one, &four, &three};
  void *non_heap_elements[] = {&one, &three, &zero, &two, &four};
  void *unique_heap_elements[] = {&zero};
  Array max_heap = array_create_from(max_heap_elements, 5);
  Array min_heap = array_create_from(min_heap_elements, 5);
  Array non_heap = array_create_from(non_heap_elements, 5);
  Array unique_heap = array_create_from(unique_heap_elements, 1);
  Array empty_heap = array_create_empty(0);

  ok(heap_check(max_heap, comparison_asc) == 1, "Must be a max-heap.");
  ok(heap_check(min_heap, comparison_asc) == 0, "Must not be a max-heap.");
  ok(heap_check(non_heap, comparison_asc) == 0, "Must not be a max-heap.");
  ok(heap_check(unique_heap, comparison_asc) == 1, "Must be a max-heap.");
  ok(heap_check(empty_heap, comparison_asc) == 1, "Must be a max-heap.");

  ok(heap_check(min_heap, comparison_desc) == 1, "Must be a min-heap.");
  ok(heap_check(max_heap, comparison_desc) == 0, "Must not be a min-heap.");
  ok(heap_check(non_heap, comparison_desc) == 0, "Must not be a min-heap.");
  ok(heap_check(unique_heap, comparison_desc) == 1, "Must be a min-heap.");
  ok(heap_check(empty_heap, comparison_desc) == 1, "Must be a min-heap.");

  array_destroy(&max_heap);
  array_destroy(&min_heap);
  array_destroy(&non_heap);
  array_destroy(&unique_heap);
  array_destroy(&empty_heap);
}

void test_heap_heapify() {
  // 10
  ComparisonFunction comparison_asc = &compare_ascending_integers;
  ComparisonFunction comparison_desc = &compare_descending_integers;
  void *max_heap_elements[] = {&four, &two, &three, &zero, &one};
  void *min_heap_elements[] = {&zero, &two, &one, &four, &three};
  void *non_heap_elements[] = {&one, &three, &zero, &two, &four};
  void *unique_heap_elements[] = {&zero};
  Array max_heap = array_create_from(max_heap_elements, 5);
  Array min_heap = array_create_from(min_heap_elements, 5);
  Array non_heap = array_create_from(non_heap_elements, 5);
  Array unique_heap = array_create_from(unique_heap_elements, 1);
  Array empty_heap = array_create_empty(0);

  heap_build(max_heap, comparison_asc);
  heap_build(min_heap, comparison_asc);
  heap_build(non_heap, comparison_asc);
  heap_build(unique_heap, comparison_asc);
  heap_build(empty_heap, comparison_asc);

  ok(heap_check(max_heap, comparison_asc) == 1, "Must be a max-heap.");
  ok(heap_check(min_heap, comparison_asc) == 1, "Must be a max-heap.");
  ok(heap_check(non_heap, comparison_asc) == 1, "Must be a max-heap.");
  ok(heap_check(unique_heap, comparison_asc) == 1, "Must be a max-heap.");
  ok(heap_check(empty_heap, comparison_asc) == 1, "Must be a max-heap.");

  heap_build(max_heap, comparison_desc);
  heap_build(min_heap, comparison_desc);
  heap_build(non_heap, comparison_desc);
  heap_build(unique_heap, comparison_desc);
  heap_build(empty_heap, comparison_desc);

  ok(heap_check(min_heap, comparison_desc) == 1, "Must be a min-heap.");
  ok(heap_check(max_heap, comparison_desc) == 1, "Must be a min-heap.");
  ok(heap_check(non_heap, comparison_desc) == 1, "Must be a min-heap.");
  ok(heap_check(unique_heap, comparison_desc) == 1, "Must be a min-heap.");
  ok(heap_check(empty_heap, comparison_desc) == 1, "Must be a min-heap.");

  array_destroy(&max_heap);
  array_destroy(&min_heap);
  array_destroy(&non_heap);
  array_destroy(&unique_heap);
  array_destroy(&empty_heap);
}

int main() {
  plan(10 + 10);

  test_heap_basics();
  test_heap_heapify();

  done_testing();
  return EXIT_SUCCESS;
}
