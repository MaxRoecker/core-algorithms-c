#include <stdio.h>
#include <tap.h>
#include "../src/structures/node.h"

int zero = 0,
    one = 1,
    two = 2,
    three = 3,
    four = 4;

void test_creation_destruction() {
  // 6
  Array third_children = array_create_empty(1);
  Node third = node_create(&three, third_children);
  array_destroy(&third_children);

  Array second_children = array_create_empty(1);
  array_set(second_children, 0, third);
  Node second = node_create(&two, second_children);
  array_destroy(&second_children);

  Array first_children = array_create_empty(1);
  array_set(first_children, 0, second);
  Node first = node_create(&one, first_children);
  array_destroy(&first_children);

  ok(*((int *) node_value(first)) == one, "First value must be 1.");
  ok(*((int *) node_value(second)) == two, "First value must be 2.");
  ok(*((int *) node_value(third)) == three, "First value must be 3.");

  Node first_child = node_child(first, 0);
  Node third_child = node_child(third, 0);
  Node second_child = node_child(second, 0);
  ok(node_equals(first_child, second) == 1,
     "First child must be equals the second node.");
  ok(node_equals(second_child, third) == 1,
     "Second child must be equals the third node.");
  ok(node_equals(third_child, ((Node) NULL)) == 1,
     "Third child must be equals to NULL");

  node_destroy(&first);
  node_destroy(&second);
  node_destroy(&third);
}

void test_clone() {
  // 4
  Array second_children = array_create_empty(1);
  Node second = node_create(&two, second_children);
  array_destroy(&second_children);

  Array first_children = array_create_empty(1);
  array_set(first_children, 0, second);
  Node first = node_create(&one, first_children);
  array_destroy(&first_children);

  Node first_clone = node_clone(first);
  Node second_clone = node_clone(second);

  ok(node_equals(first, first_clone) == 1, "Cloned nodes must be equals.");
  ok(node_equals(second, second_clone) == 1, "Cloned nodes must be equals.");
  ok(node_equals(first, second_clone) == 0, "Must not be equals.");
  ok(node_equals(second, first_clone) == 0, "Must not be equals.");

  node_destroy(&first);
  node_destroy(&second);
  node_destroy(&first_clone);
  node_destroy(&second_clone);
}

int main() {
  plan(6 + 4);

  test_creation_destruction();
  test_clone();

  done_testing();
  return EXIT_SUCCESS;
}
