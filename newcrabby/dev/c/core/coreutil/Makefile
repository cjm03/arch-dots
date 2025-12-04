# Makefile

CC := gcc
CFLAGS := -O2 -g -Wall -Wextra -pedantic -std=c99

TARGETS := cls crm cedit ccat
SHARED_SRC := help.c
SHARED_OBJ := $(SHARED_SRC:.c=.o)

all: clean build

# build all 
build: $(TARGETS)

# build exe from .c and gen .d 
%: %.c
	$(CC) $(CFLAGS) $(SHARED_SRC) $< -o $@

# .d -> .c
-include $(TARGETS:=.d)

# generate .d files for each .c
%.d: %.c
	@$(CC) $(CFLAGS) -MM $< > $@

# clean
clean:
	rm -f $(TARGETS) *.o *.d

.PHONY: all clean
