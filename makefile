SHELL=/bin/sh
CC=gcc
CFLAGS= -std=c99
SRC=src
BIN=bin

MEMORY_FILES=src/commons/memory.h src/commons/memory.c
ARRAY_FILES=src/structures/array.h src/structures/array.c

test-memory:
	mkdir -p $(BIN)
	$(CC) -o $(BIN)/memory_tests tests/commons_memory.c $(MEMORY_FILES) -ltap $(CFLAGS)
	./$(BIN)/memory_tests

test-structure-array:
	mkdir -p $(BIN)
	$(CC) -o $(BIN)/array_tests tests/structures_array_tests.c $(ARRAY_FILES) $(MEMORY_FILES) -ltap $(CFLAGS)
	./$(BIN)/array_tests

test-sorting:
	mkdir -p $(BIN)
	$(CC) -o $(BIN)/sorting_tests tests/sorting_tests.c src/sorting/sorting.h src/sorting/sorting.c $(ARRAY_FILES) $(MEMORY_FILES) -ltap $(CFLAGS)
	./$(BIN)/sorting_tests

clean:
	rm -r bin/*
