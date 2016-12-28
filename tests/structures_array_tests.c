#include <stdio.h>
#include <tap.h>
#include "../src/structures/array.h"

int zero = 0,
    one = 1,
    two = 2,
    three = 3,
    four = 4;

char comparison_as_integer(void *const one, void *const another) {
  int one_value = *((int *) one);
  int another_value = *((int *) another);
  return (char) one_value > another_value;
};

void test_creation_destruction() {
  // 29
  const size_t size = 10;
  Array a = array_create_empty(size);
  Array b = array_create_empty(size);
  Array c = array_create_empty(0);
  Array d = array_create_empty(0);

  ok(array_lenght(a) == 10, "Must be equal to %lu.", size);
  ok(array_lenght(b) == 10, "Must be equal to %lu.", size);
  ok(array_equals(a, b) == 1, "Must be true.");

  for (size_t i = 0; i < size; i += 1) {
    ok(array_get(a, i) == NULL, "Item %lu of a must be NULL.", i);
    ok(array_get(a, i) == NULL, "Item %lu of b must be NULL.", i);
  }

  ok(array_equals(c, d) == 1, "Empty arrays must be equals.");
  ok(array_equals(d, c) == 1, "Empty arrays must be equals.");

  array_destroy(&a);
  array_destroy(&b);
  array_destroy(&c);
  array_destroy(&d);
  ok(a == NULL, "Must be NULL.");
  ok(b == NULL, "Must be NULL.");
  ok(c == NULL, "Must be NULL.");
  ok(d == NULL, "Must be NULL.");
}

void test_copy() {
  // 1
  void *elements[] = {&zero, &one, &two, &three, &four};
  Array full = array_create_from(elements, 5);
  Array empty = array_copy(full);

  ok(array_equals(empty, full) == 1, "Copied arrays must be equals.");

  array_destroy(&full);
  array_destroy(&empty);
}

void test_slice() {
  // 5
  void *a[] = {&zero, &one, &two, &three, &four};
  void *b[] = {&zero, &one};
  void *c[] = {&two};
  void *d[] = {&three, &four};
  void *e[] = {};
  Array complete = array_create_from(a, 5);
  Array prefix = array_create_from(b, 2);
  Array infix = array_create_from(c, 1);
  Array suffix = array_create_from(d, 2);
  Array empty = array_create_from(e, 0);

  Array slice_prefix = array_slice(complete, 0, 2);
  Array slice_infix = array_slice(complete, 2, 3);
  Array slice_suffix = array_slice(complete, 3, 5);
  Array slice_empty = array_slice(complete, 5, 5);
  Array slice_complete = array_slice(complete, 0, 5);

  ok(array_equals(prefix, slice_prefix) == 1, "Must be prefix.");
  ok(array_equals(infix, slice_infix) == 1, "Must be infix.");
  ok(array_equals(suffix, slice_suffix) == 1, "Must be suffix.");
  ok(array_equals(empty, slice_empty) == 1, "Must be empty.");
  ok(array_equals(complete, slice_complete) == 1, "Must be equals.");

  array_destroy(&complete);
  array_destroy(&prefix);
  array_destroy(&infix);
  array_destroy(&suffix);
  array_destroy(&empty);
  array_destroy(&slice_prefix);
  array_destroy(&slice_infix);
  array_destroy(&slice_suffix);
  array_destroy(&slice_empty);
  array_destroy(&slice_complete);
}

void test_merge() {
  // 3
  void *a[] = {&zero, &one, &two, &three, &four};
  void *b[] = {&zero, &two, &four};
  void *c[] = {&one, &three};
  Array complete = array_create_from(a, 5);
  Array one = array_create_from(b, 3);
  Array another = array_create_from(c, 2);
  Array empty = array_create_empty(0);
  ComparisonFunction comparison = &comparison_as_integer;

  Array one_merge = array_merge(one, another, comparison);
  ok(array_equals(one_merge, complete) == 1, "Arrays must be equals.");

  Array another_merge = array_merge(another, one, comparison);
  ok(array_equals(another_merge, complete) == 1, "Arrays must be equals.");

  Array complete_merge = array_merge(empty, complete, comparison);
  ok(array_equals(complete_merge, complete) == 1, "Arrays must be equals.");

  array_destroy(&complete);
  array_destroy(&one);
  array_destroy(&another);
  array_destroy(&empty);
  array_destroy(&one_merge);
  array_destroy(&another_merge);
  array_destroy(&complete_merge);
}

void test_merge_into() {
  // 4
  void *a_elements[] = {&zero, &four, &two, &three, &one};
  void *b_elements[] = {&zero, &two, &four, &three, &one};
  void *c_elements[] = {&zero, &two, &four, &one, &three};
  void *d_elements[] = {&zero, &one, &two, &three, &four};
  Array a = array_create_from(a_elements, 5);
  Array b = array_create_from(b_elements, 5);
  Array c = array_create_from(c_elements, 5);
  Array d = array_create_from(d_elements, 5);
  ComparisonFunction comparison = &comparison_as_integer;

  array_merge_into(a, 0, 2, 3, comparison);
  ok(array_equals(a, b) == 1, "Must be equals.");

  array_merge_into(a, 3, 4, 5, comparison);
  ok(array_equals(a, c) == 1, "Must be equals.");

  array_merge_into(a, 0, 3, 5, comparison);
  ok(array_equals(a, d) == 1, "Must be equals.");

  array_merge_into(a, 4, 4, 5, comparison);
  ok(array_equals(a, d) == 1, "Must be equals.");

  array_destroy(&a);
  array_destroy(&b);
  array_destroy(&c);
  array_destroy(&d);
}


int main() {
  plan(29 + 1 + 5 + 3 + 4);

  test_creation_destruction();
  test_copy();
  test_slice();
  test_merge();
  test_merge_into();

  done_testing();
  return EXIT_SUCCESS;
}
