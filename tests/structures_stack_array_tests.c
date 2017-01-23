#include <stdio.h>
#include <tap.h>
#include "../src/structures/stack_array.h"

int zero = 0,
    one = 1,
    two = 2,
    three = 3,
    four = 4;

void test_creation_destruction() {
  // 9
  Array empty = array_create_empty(0);

  StackArray a = stackarray_create();
  Array a_array = stackarray_as_array(a);
  ok(stackarray_lenght(a) == 0, "Must have lenght of %d.", 0);
  ok(stackarray_empty(a) == 1, "Must be empty.");
  ok(array_equals(empty, a_array) == 1, "Must be equals.");
  array_destroy(&a_array);
  stackarray_destroy(&a);

  StackArray b = stackarray_create_of(empty);
  Array b_array = stackarray_as_array(b);
  ok(stackarray_lenght(b) == 0, "Must have length of %d.", 0);
  ok(stackarray_empty(b) == 1, "Must be empty.");
  ok(array_equals(empty, b_array) == 1, "Must be equals.");
  array_destroy(&b_array);
  stackarray_destroy(&b);

  void *elements[] = {&zero, &one, &two, &three, &four};
  Array full = array_create_from(elements, 5);
  StackArray d = stackarray_create_of(full);
  Array d_array = stackarray_as_array(d);
  ok(stackarray_lenght(d) == 5, "Must have length of %d.", 5);
  ok(stackarray_empty(d) == 0, "Must not be empty.");
  ok(array_equals(full, d_array) == 1, "Must be equals.");
  array_destroy(&d_array);
  stackarray_destroy(&d);

  array_destroy(&empty);
}

void test_stack() {
  // 4
  StackArray stack = stackarray_create();

  stackarray_push(stack, &zero);
  ok((stackarray_pop(stack) == &zero) == 1, "Must be the same.");

  stackarray_push(stack, &one);
  stackarray_push(stack, &two);
  stackarray_push(stack, &three);
  ok((stackarray_pop(stack) == &three) == 1, "Must be equals.");
  ok((stackarray_pop(stack) == &two) == 1, "Must be equals.");
  ok((stackarray_pop(stack) == &one) == 1, "Must be equals.");

  stackarray_destroy(&stack);
}

int main() {
  plan(9 + 4);

  test_creation_destruction();
  test_stack();

  done_testing();
  return EXIT_SUCCESS;
}
