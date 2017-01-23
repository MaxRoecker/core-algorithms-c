#include <stdio.h>
#include <tap.h>
#include "../src/structures/list_array.h"

int zero = 0,
    one = 1,
    two = 2,
    three = 3,
    four = 4;

char compare_ascending(void *const one, void *const another) {
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

void test_remove() {
  // 6
  void *ints[] = {&zero, &one, &two, &three, &four};
  Array full = array_create_from(ints, 5);
  ListArray list = listarray_create_of(full);
  array_destroy(&full);

  ok((listarray_remove(list, 1) == &one) == 1, "Must be equals.");
  ok((listarray_remove(list, 2) == &three) == 1, "Must be equals.");
  ok((listarray_remove(list, 2) == &four) == 1, "Must be equals.");
  ok((listarray_remove(list, 0) == &zero) == 1, "Must be equals.");
  ok((listarray_remove(list, 0) == &two) == 1, "Must be equals.");
  ok((listarray_lenght(list) == 0) == 1, "Must be empty.");
}

void test_queue() {
  // 4
  ListArray queue = listarray_create();

  listarray_enqueue(queue, &zero);
  ok((listarray_dequeue(queue) == &zero) == 1, "Must be the same.");

  listarray_enqueue(queue, &one);
  listarray_enqueue(queue, &two);
  listarray_enqueue(queue, &three);

  ok((listarray_dequeue(queue) == &one) == 1, "Must be equals.");
  ok((listarray_dequeue(queue) == &two) == 1, "Must be equals.");
  ok((listarray_dequeue(queue) == &three) == 1, "Must be equals.");
}

void test_stack() {
  // 4
  ListArray stack = listarray_create();

  listarray_push(stack, &zero);
  ok((listarray_pop(stack) == &zero) == 1, "Must be the same.");

  listarray_push(stack, &one);
  listarray_push(stack, &two);
  listarray_push(stack, &three);

  ok((listarray_pop(stack) == &three) == 1, "Must be equals.");
  ok((listarray_pop(stack) == &two) == 1, "Must be equals.");
  ok((listarray_pop(stack) == &one) == 1, "Must be equals.");
}

void test_max_min() {
  // 4
  void *full_ints[] = {&zero, &one, &two, &three, &four};
  Array full_array = array_create_from(full_ints, 5);
  ListArray full = listarray_create_of(full_array);
  array_destroy(&full_array);

  void *uniq_ints[] = {&zero};
  Array uniq_array = array_create_from(uniq_ints, 1);
  ListArray uniq = listarray_create_of(uniq_array);
  array_destroy(&uniq_array);

  ComparisonFunction comparison = &compare_ascending;

  ok((listarray_max(full, comparison) == 4) == 1, "Must be equals.");
  ok((listarray_max(uniq, comparison) == 0) == 1, "Must be equals.");
  ok((listarray_min(full, comparison) == 0) == 1, "Must be equals.");
  ok((listarray_min(uniq, comparison) == 0) == 1, "Must be equals.");
}

int main() {
  plan(8 + 10 + 6 + 6 + 4 + 4 + 4);

  test_creation_destruction();
  test_get();
  test_insert();
  test_remove();
  test_queue();
  test_stack();
  test_max_min();

  done_testing();
  return EXIT_SUCCESS;
}
