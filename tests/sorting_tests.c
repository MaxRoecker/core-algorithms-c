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


char comparison_as_integer(void *const one, void *const another) {
  int one_value = *((int *) one);
  int another_value = *((int *) another);
  return one_value > another_value;
}


void test_insertion_sort(void) {
  // 3
  ComparisonFunction comparison = &comparison_as_integer;
  Array sorted = array_create_from(sorted_ints, 10);

  Array unsorted = array_create_from(unsorted_ints, 10);
  insertion_sort(&unsorted, comparison);
  ok(array_equals(&unsorted, &sorted) == 1, "Must be sorted.");

  Array reverse = array_create_from(reverse_ints, 10);
  insertion_sort(&reverse, comparison);
  ok(array_equals(&reverse, &sorted) == 1, "Must be sorted.");

  Array already_sorted = array_create_from(sorted_ints, 10);
  insertion_sort(&already_sorted, comparison);
  ok(array_equals(&already_sorted, &sorted) == 1, "Must be sorted.");
}

int main() {
  plan(3);

  test_insertion_sort();

  done_testing();
  return EXIT_SUCCESS;
}
