#include <stdio.h>
#include <tap.h>
#include "../src/sorting/sorting.h"


int zero = 0, one = 1, two = 2, three = 3, four = 4, five = 5, six = 6,
    seven = 7, eight = 8, nine = 9;
void *sorted_ints[] = {&zero, &one, &two, &three, &four, &five, &six, &seven,
                       &eight, &nine};
void *unsorted_ints[] = {&one, &zero, &two, &three, &six, &five, &seven, &four,
                         &nine, &eight};
void *reverse_ints[] = {&nine, &eight, &seven, &six, &five, &four, &three, &two,
                        &one, &zero};


char compare_ascending(void *const one, void *const another) {
  int one_value = *((int *) one);
  int another_value = *((int *) another);
  return one_value > another_value;
}

char compare_descending(void *const one, void *const another) {
  int one_value = *((int *) one);
  int another_value = *((int *) another);
  return one_value < another_value;
}


void test_insertion_sort(void) {
  // 6
  ComparisonFunction comparison_asc = &compare_ascending;
  ComparisonFunction comparison_desc = &compare_descending;
  Array sorted = array_create_from(sorted_ints, 10);
  Array reverse = array_create_from(reverse_ints, 10);
  Array unsorted = array_create_from(unsorted_ints, 10);

  Array unsorted_sorted_asc = insertion_sort(unsorted, comparison_asc);
  Array unsorted_sorted_desc = insertion_sort(unsorted, comparison_desc);
  ok(array_equals(unsorted_sorted_asc, sorted) == 1,
     "Must be asceding sorted.");
  ok(array_equals(unsorted_sorted_desc, reverse) == 1,
     "Must be descending sorted.");

  Array sorted_sorted_asc = insertion_sort(sorted, comparison_asc);
  Array sorted_sorted_desc = insertion_sort(sorted, comparison_desc);
  ok(array_equals(unsorted_sorted_asc, sorted) == 1,
     "Must be asceding sorted.");
  ok(array_equals(unsorted_sorted_desc, reverse) == 1,
     "Must be descending sorted.");

  Array reverse_sorted_asc = insertion_sort(reverse, comparison_asc);
  Array reverse_sorted_desc = insertion_sort(reverse, comparison_desc);
  ok(array_equals(unsorted_sorted_asc, sorted) == 1,
     "Must be asceding sorted.");
  ok(array_equals(unsorted_sorted_desc, reverse) == 1,
     "Must be descending sorted.");

  array_destroy(&sorted);
  array_destroy(&reverse);
  array_destroy(&unsorted);
  array_destroy(&unsorted_sorted_asc);
  array_destroy(&unsorted_sorted_desc);
  array_destroy(&sorted_sorted_asc);
  array_destroy(&sorted_sorted_desc);
  array_destroy(&reverse_sorted_asc);
  array_destroy(&reverse_sorted_desc);
}

int main() {
  plan(6);

  test_insertion_sort();

  done_testing();
  return EXIT_SUCCESS;
}
