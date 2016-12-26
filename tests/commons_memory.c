#include <stdio.h>
#include <tap.h>
#include "../src/commons/memory.h"

int main() {
  const size_t max = 10;
  plan(max);

  int *address = (int *) memory_alloc(sizeof(int) * max);
  for (size_t i = 0; i < max; i++) {
    address[i] = i;
  }
  for (size_t i = 0; i < max; i++) {
    ok(address[i] == i, "Must be equal.");
  }

  free(address);
  address = NULL;

  done_testing();
  return EXIT_SUCCESS;
}
