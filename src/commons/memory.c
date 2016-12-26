#include "memory.h"

void *memory_alloc(size_t size) {
  void *address = malloc(size);
  if (address == NULL) {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
  }
  return address;
}
