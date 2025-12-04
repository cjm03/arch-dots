# Makefile
CC=gcc
CFLAGS=-O2 -Wall -pedantic -std=c99
SRC=curses.c util.c ansi.c
TARGET=curses

all: clean curses

.PHONY: curses
curses:
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

clean:
	@if [ -f $(TARGET) ]; then \
		rm -f $(TARGET); \
	fi
