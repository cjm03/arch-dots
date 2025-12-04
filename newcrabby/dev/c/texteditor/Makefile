# Makefile

CC=gcc
CFLAGS=-O2 -g -Wall -Wextra -pedantic -std=c99
SRC=ecrab.c
TARGET=ec

all: clean build

build:
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

.PHONY: clean
clean:
	@if [ -f $(TARGET) ]; then \
		rm -f $(TARGET); \
	fi
