 CC = gcc
CFLAGS = -Wall -Werror

all: program

program: main.o encryption.o Huffman.o
	$(CC) $(CFLAGS) -o program main.o encryption.o Huffman.o

main.o: main.c encryption.h Huffman.h
	$(CC) $(CFLAGS) -c main.c

encryption.o: encryption.c encryption.h
	$(CC) $(CFLAGS) -c encryption.c

Huffman.o: Huffman.c Huffman.h
	$(CC) $(CFLAGS) -c Huffman.c

.PHONY: clean

clean:
	rm -f program *.o
