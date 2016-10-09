CC = gcc
CFLAGS = -g -Wall -std=c99 -D_GNU_SOURCE
LDLIBS = -lm

all: cross connect

cross: cross.o

connect: board.o

connect.o: board.h
board.o: board.h

clean:
	rm -f cross cross.o
	rm -f connect connect.o
	rm -f board board.o
	rm -f output.txt
	rm -f stderr.txt