CC=gcc
CFLAGS=-Wall -Werror

.PHONY: clean

build: tema2

tema2: trie.c queue.h
	$(CC) trie.c $(CFLAGS) -o trie

clean:
	rm -f trie