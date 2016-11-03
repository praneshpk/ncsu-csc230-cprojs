CC = gcc
CFLAGS = -g -Wall -std=c99 -D_GNU_SOURCE
LDLIBS = -lm

all: daily
daily: daily.o activity.o schedule.o

daily.o: activity.h schedule.h
activity.o: activity.h
schedule.o: schedule.h activity.h

clean:
	rm -f daily daily.o
	rm -f activity activity.o
	rm -f schedule schedule.o
	rm -f output.txt
	rm -f stderr.txt