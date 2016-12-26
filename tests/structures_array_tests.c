#include <stdio.h>
#include <tap.h>
#include "../src/structures/array.h"

int zero = 0,
    one = 1,
    two = 2,
    three = 3,
    four = 4;

int main() {
  plan(11);

  // Basic Tests
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

  done_testing();
  return EXIT_SUCCESS;
}
