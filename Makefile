CC=gcc
CFLAGS=-lncurses -I.

mousing: mousing.o
	$(CC) -o mousing mousing.o $(CFLAGS)
