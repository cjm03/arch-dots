# Makefile
CC=gcc
CFLAGS=-pedantic -Wextra -Wall -g -c

all: aes main linking

linking:
	$(CC) -o aes.exe aes.o main.o
main:
	$(CC) $(CFLAGS) main.c -o main.o
aes:
	$(CC) $(CFLAGS) aes.c -o aes.o
