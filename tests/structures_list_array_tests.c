#include <stdio.h>
#include <tap.h>
#include "../src/structures/list_array.h"

int zero = 0,
    one = 1,
    two = 2,
    three = 3,
    four = 4;

void test_creation_destruction() {
  // 8
  ListArray a = listarray_create();
  ok(listarray_lenght(a) == 0, "Must have lenght of %d.", 0);
  ok(listarray_empty(a) == 1, "Must be empty.");

  Array empty = array_create_empty(0);
  ListArray b = listarray_create_of(empty);
  array_destroy(&empty);
  ok(listarray_lenght(b) == 0, "Must have length of %d.", 0);
  ok(listarray_empty(b) == 1, "Must be empty.");

  ListArray c = listarray_create_with(7);
  ok(listarray_lenght(c) == 0, "Must have lenght of %d.", 0);
  ok(listarray_empty(c) == 1, "Must be empty.");

  void *elements[] = {&zero, &one, &two, &three, &four};
  Array full = array_create_from(elements, 5);
  ListArray d = listarray_create_of(full);
  array_destroy(&full);
  ok(listarray_lenght(d) == 5, "Must have length of %d.", 5);
  ok(listarray_empty(d) == 0, "Must not be empty.");

  listarray_destroy(&a);
  listarray_destroy(&b);
  listarray_destroy(&c);
  listarray_destroy(&d);
}

void test_get() {
  // 10
  void *ints[] = {&zero, &one, &two, &three, &four};
  Array full = array_create_from(ints, 5);
  ListArray list = listarray_create_of(full);
  array_destroy(&full);

  for (size_t i = 0; i < 5; i += 1) {
    unsigned char equality = (ints[i] == listarray_get(list, i));
    ok(equality == 1, "Must be equals.");
  }

  for (size_t i = 0; i < 5; i += 1) {
    size_t index = listarray_index_of(list, ints[i]);
    ok(index == i, "Must be equals.");
  }
}

void test_insert() {
  // 6
  ListArray list = listarray_create();
  listarray_insert(list, 0, &two);
  listarray_insert(list, 1, &four);
  listarray_insert(list, 0, &zero);
  listarray_insert(list, 1, &one);
  listarray_insert(list, 3, &three);

  ok(listarray_lenght(list) == 5, "Must be lenght of %d.", 5);
  ok((listarray_get(list, 0) == &zero) == 1, "Must be equals.");
  ok((listarray_get(list, 1) == &one) == 1, "Must be equals.");
  ok((listarray_get(list, 2) == &two) == 1, "Must be equals.");
  ok((listarray_get(list, 3) == &three) == 1, "Must be equals.");
  ok((listarray_get(list, 4) == &four) == 1, "Must be equals.");
}


int main() {
  plan(8 + 10 + 6);

  test_creation_destruction();
  test_get();
  test_insert();

  done_testing();
  return EXIT_SUCCESS;
}
