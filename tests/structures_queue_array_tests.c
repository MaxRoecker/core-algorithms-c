#include <stdio.h>
#include <tap.h>
#include "../src/structures/queue_array.h"

int zero = 0,
    one = 1,
    two = 2,
    three = 3,
    four = 4;

void test_creation_destruction() {
  // 9
  Array empty = array_create_empty(0);

  QueueArray a = queuearray_create();
  Array a_array = queuearray_as_array(a);
  ok(queuearray_lenght(a) == 0, "Must have lenght of %d.", 0);
  ok(queuearray_empty(a) == 1, "Must be empty.");
  ok(array_equals(empty, a_array) == 1, "Must be equals.");
  array_destroy(&a_array);
  queuearray_destroy(&a);

  QueueArray b = queuearray_create_of(empty);
  Array b_array = queuearray_as_array(b);
  ok(queuearray_lenght(b) == 0, "Must have length of %d.", 0);
  ok(queuearray_empty(b) == 1, "Must be empty.");
  ok(array_equals(empty, b_array) == 1, "Must be equals.");
  array_destroy(&b_array);
  queuearray_destroy(&b);

  void *elements[] = {&zero, &one, &two, &three, &four};
  Array full = array_create_from(elements, 5);
  QueueArray d = queuearray_create_of(full);
  Array d_array = queuearray_as_array(d);
  ok(queuearray_lenght(d) == 5, "Must have length of %d.", 5);
  ok(queuearray_empty(d) == 0, "Must not be empty.");
  ok(array_equals(full, d_array) == 1, "Must be equals.");
  array_destroy(&d_array);
  queuearray_destroy(&d);

  array_destroy(&empty);
}

void test_queue() {
  // 4
  QueueArray queue = queuearray_create();

  queuearray_enqueue(queue, &zero);
  ok((queuearray_dequeue(queue) == &zero) == 1, "Must be the same.");

  queuearray_enqueue(queue, &one);
  queuearray_enqueue(queue, &two);
  queuearray_enqueue(queue, &three);
  ok((queuearray_dequeue(queue) == &one) == 1, "Must be equals.");
  ok((queuearray_dequeue(queue) == &two) == 1, "Must be equals.");
  ok((queuearray_dequeue(queue) == &three) == 1, "Must be equals.");

  queuearray_destroy(&queue);
}

int main() {
  plan(9 + 4);

  test_creation_destruction();
  test_queue();

  done_testing();
  return EXIT_SUCCESS;
}
