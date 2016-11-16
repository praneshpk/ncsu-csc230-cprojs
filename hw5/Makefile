CC = gcc
CFLAGS = -g -Wall -std=c99 -D_GNU_SOURCE
LDLIBS = -lm

all: squeeze unsqueeze

squeeze: squeeze.o codes.o bits.o
squeeze.o: codes.h bits.h

unsqueeze: unsqueeze.o codes.o bits.o
unsqueeze.o: codes.h bits.h

codes.o: codes.h
bits.o: bits.h

clean:
	rm -f squeeze squeeze.o
	rm -f unsqueeze unsqueeze.o
	rm -f bits.o codes.o
	rm -f output.txt
	rm -f stderr.txt