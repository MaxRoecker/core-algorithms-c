#include <stdio.h>
#include <tap.h>
#include "../src/structures/array.h"

int zero = 0,
    one = 1,
    two = 2,
    three = 3,
    four = 4;

char basic_comparison_as_integer(void *const one, void *const another) {
  int one_value = *((int *) one);
  int another_value = *((int *) another);
  return (char) one_value > another_value;
};

void test_basics() {
  // 11
  Array a = array_create_empty(10);
  Array b = array_create_empty(10);
  ok(a.length == 10, "Must be equal.");
  ok(array_equals(&a, &b) == 1, "Must be true.");
  ok(array_get(&a, 0) == NULL, "Must be NULL.");

  void *removed_value = array_set(&a, 0, &one);
  ok(removed_value == NULL, "Must be NULL.");
  ok(*((int *) array_get(&a, 0)) == one, "Must be 1.");

  void *integers[] = {&zero, &one, &two, &three, &four};
  Array c = array_create_from(integers, 5);
  for (size_t i = 0; i < c.length; i++) {
    ok(array_get(&c, i) == integers[i], "Must be equal.");
  }

  Array d = array_create_from(integers, 5);
  ok(array_equals(&c, &d) == 1, "Must be true.");
}

void test_splice() {
  // 3
  void *a[] = {&zero, &one, &two, &three, &four};
  void *b[] = {&zero, &one, &two};
  void *c[] = {&one, &two, &three};
  void *d[] = {&three, &four};
  Array complete = array_create_from(a, 5);
  Array prefix = array_create_from(b, 3);
  Array infix = array_create_from(c, 3);
  Array suffix = array_create_from(d, 2);

  Array slice_prefix = array_slice(&complete, 0, 3);
  Array slice_infix = array_slice(&complete, 1, 4);
  Array slice_suffix = array_slice(&complete, 3, 5);

  ok(array_equals(&prefix, &slice_prefix) == 1, "Must be prefix.");
  ok(array_equals(&infix, &slice_infix) == 1, "Must be prefix.");
  ok(array_equals(&suffix, &slice_suffix) == 1, "Must be prefix.");
}

void test_merge() {
  // 1
  void *a[] = {&zero, &one, &two, &three, &four};
  void *b[] = {&zero, &two, &four};
  void *c[] = {&one, &three};
  Array complete = array_create_from(a, 5);
  Array one = array_create_from(b, 3);
  Array another = array_create_from(c, 2);
  basic_comparison comparison = &basic_comparison_as_integer;
  Array merged = array_merge(&one, &another, comparison);
  ok(array_equals(&merged, &complete) == 1, "Must be equals.");
}

int main() {
  plan(11 + 3 + 1);

  test_basics();
  test_splice();
  test_merge();

  done_testing();
  return EXIT_SUCCESS;
}
