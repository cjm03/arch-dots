# Makefile

CC=gcc
CFLAGS=-O2 -g -Wall -Wextra -pedantic -std=c99

LSSRC=ls.c
LSTARGET=crabls

RMSRC=rm.c
RMTARGET=crabrm

ECSRC=textedit.c
ECTARGET=crabedit

TARGETS=crabls crabrm crabedit


all: crabls crabrm crabedit


.PHONY: crabls
crabls:
	rm -f $(LSTARGET) && $(CC) $(LSSRC) $(CFLAGS) -o $(LSTARGET)

.PHONY: crabrm
crabrm: 
	rm -f $(RMTARGET) && $(CC) $(RMSRC) $(CFLAGS) -o $(RMTARGET)

.PHONY: crabedit
crabedit:
	rm -f $(ECTARGET) && $(CC) $(ECSRC) $(CFLAGS) -o $(ECTARGET)

.PHONY: clean
clean:
	rm -f $(TARGETS)
