# Makefile

CC=gcc
CFLAGS=-g -O2 -Wall -Wextra -pedantic -std=c99
SRC=src/mem.c src/str.c src/mmath.c
TARGETOBJS=mem.o str.o mmath.o
TARGETLIB=libcrabc.a
ATESTBIN=arenatest
STESTBIN=strtest
MTESTBIN=mtest
DTESTBIN=datatest


all: clean build


.PHONY: arenatest
arenatest:
	@if [ -f $(ATESTBIN) ]; then \
		rm -f $(ATESTBIN); \
	fi
	$(CC) $(SRC) tests/arenatest.c $(CFLAGS) -o $(ATESTBIN)


.PHONY: strtest
strtest:
	@if [ -f $(STESTBIN) ]; then \
		rm -f $(STESTBIN); \
	fi
	$(CC) $(SRC) tests/stringtest.c $(CFLAGS) -o $(STESTBIN)


.PHONY: mtest
mtest: 
	@if [ -f $(MTESTBIN) ]; then \
		rm -f $(MTESTBIN); \
	fi
	$(CC) $(SRC) tests/mathtest.c $(CFLAGS) -o $(MTESTBIN)


.PHONY: datatest
datatest:
	@if [ -f $(DTESTBIN) ]; then \
		rm -f $(DTESTBIN); \
	fi
	$(CC) tests/datatest.c src/data.c $(CFLAGS) -o $(DTESTBIN)


build:
	@echo "Compiling objects..."
	$(CC) -c $(SRC) $(CFLAGS)
	@echo "Compiled objects"
	@echo "Bundling..."
	ar rcs $(TARGETLIB) $(TARGETOBJS)
	@echo "Bundling complete, generated $(TARGETLIB)"
	rm -f $(TARGETOBJS)


.PHONY: clean
clean:
	@echo "Checking for existing library..."
	@if [ -f $(TARGETLIB) ]; then \
		echo "Removing old library file $(TARGETLIB)..."; \
		rm -f $(TARGETLIB); \
	else \
		echo "$(TARGETLIB) not found"; \
	fi
