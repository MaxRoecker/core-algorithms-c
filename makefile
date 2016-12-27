SHELL=/bin/sh
CC=gcc
CFLAGS= -std=c99
SRC=src
BIN=bin

COMMONS_PACK=$(SRC)/commons
SORTING_PACK=$(SRC)/sorting
STRUCTURES_PACK=$(SRC)/structures

MEMORY_MOD=$(COMMONS_PACK)/memory.h $(COMMONS_PACK)/memory.c
COMPARISON_MOD=$(COMMONS_PACK)/comparison.h
ARRAY_MOD=$(STRUCTURES_PACK)/array.h $(STRUCTURES_PACK)/array.c $(MEMORY_MOD)
SORTING_MOD=$(SORTING_PACK)/sorting.h $(SORTING_PACK)/sorting.c $(ARRAY_MOD)

test-memory:
	mkdir -p $(BIN)
	$(CC) -o $(BIN)/memory_tests tests/commons_memory.c $(MEMORY_MOD) -ltap $(CFLAGS)
	./$(BIN)/memory_tests

test-structure-array:
	mkdir -p $(BIN)
	$(CC) -o $(BIN)/array_tests tests/structures_array_tests.c $(ARRAY_MOD) -ltap $(CFLAGS)
	./$(BIN)/array_tests

test-sorting:
	mkdir -p $(BIN)
	$(CC) -o $(BIN)/sorting_tests tests/sorting_tests.c $(SORTING_MOD) -ltap $(CFLAGS)
	./$(BIN)/sorting_tests

clean:
	rm -r bin/*
