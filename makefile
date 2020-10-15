CFLAGS = -std=c99 -g -pedantic -Wall
CC = gcc

all: list.o list.h

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

test1.o: test1.c
	$(CC) $(CFLAGS) -c test1.c -o test1.o

test1: test1.o list.c list.h
	$(CC) $(CFLAGS) test1.o list.o -o test1

test2.o: test2.c
	$(CC) $(CFLAGS) -DLIST -c test2.c -o test2.o

test2: test2.o list.c list.h
	$(CC) $(CFLAGS) -DLIST test2.o list.o -o test2

test3.o: test3.c
	$(CC) $(CFLAGS) -c test3.c -o test3.o

test3: test3.o list.c list.h
	$(CC) $(CFLAGS) test3.o list.o -o test3

clean:
	rm *.o
