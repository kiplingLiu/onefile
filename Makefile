.POSIX:
SHELL = /bin/sh
CC = gcc
CFLAGS = -D_GNU_SOURCE -std=c99 -pedantic -Wall -g -O2

all:
f2c: f2c.o help.o help.h
	$(CC) -o $@ $(CFLAGS) f2c.o help.o
hashtab: hashtab.h
	$(CC) -DHASHTAB_TEST -o $@ $(CFLAGS) hashtab.c
help: help.h
	$(CC) -DHELP_TEST -o $@ $(CFLAGS) help.c
vector: vector.h
	$(CC) -DVECTOR_TEST -o $@ $(CFLAGS) vector.c
clean:
	rm -f *.o
	for f in *; do if [ -x "$$f" ]; then rm -f "$$f"; fi; done

.SUFFIXES:
.SUFFIXES: .o .c
