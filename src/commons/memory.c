#include "memory.h"

/**
 * Allocates memory, checking if it can be allocated.
 */
void *memory_alloc(size_t size) {
  void *address = malloc(size);
  if (address == NULL) {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
  }
  return address;
}
