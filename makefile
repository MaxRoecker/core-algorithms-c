SHELL=/bin/sh
CC=clang
SRC=src
BIN=bin

COMMONS_PACK=$(SRC)/commons
SORTING_PACK=$(SRC)/sorting
STRUCTURES_PACK=$(SRC)/structures

MEMORY_MOD=$(COMMONS_PACK)/memory.h $(COMMONS_PACK)/memory.c
COMPARISON_MOD=$(COMMONS_PACK)/comparison.h
ARRAY_MOD=$(STRUCTURES_PACK)/array.h $(STRUCTURES_PACK)/array.c $(MEMORY_MOD)
NODE_MOD=$(STRUCTURES_PACK)/node.h $(STRUCTURES_PACK)/node.c $(ARRAY_MOD)
HEAP_MOD=$(STRUCTURES_PACK)/heap.h $(STRUCTURES_PACK)/heap.c $(ARRAY_MOD)
LIST_ARRAY_MOD=$(STRUCTURES_PACK)/list_array.h $(STRUCTURES_PACK)/list_array.c $(ARRAY_MOD)
SORTING_MOD=$(SORTING_PACK)/sorting.h $(SORTING_PACK)/sorting.c $(HEAP_MOD)

test-memory:
	mkdir -p $(BIN)
	$(CC) -o $(BIN)/memory_tests -x c -ltap tests/commons_memory.c $(MEMORY_MOD)
	./$(BIN)/memory_tests

test-structure-array:
	mkdir -p $(BIN)
	$(CC) -o $(BIN)/array_tests -x c -ltap tests/structures_array_tests.c $(ARRAY_MOD)
	./$(BIN)/array_tests

test-structure-node:
	mkdir -p $(BIN)
	$(CC) -o $(BIN)/node_tests -x c -ltap tests/structures_node_tests.c $(NODE_MOD)
	./$(BIN)/node_tests

test-structure-list-array:
	mkdir -p $(BIN)
	$(CC) -o $(BIN)/list_array_tests -x c -ltap tests/structures_list_array_tests.c $(LIST_ARRAY_MOD)
	./$(BIN)/list_array_tests

test-structure-heap:
	mkdir -p $(BIN)
	$(CC) -o $(BIN)/heap_tests -x c -ltap tests/structures_heap_tests.c $(HEAP_MOD)
	./$(BIN)/heap_tests

test-sorting:
	mkdir -p $(BIN)
	$(CC) -o $(BIN)/sorting_tests -x c -ltap tests/sorting_tests.c $(SORTING_MOD)
	./$(BIN)/sorting_tests

clean:
	rm -r bin/*
