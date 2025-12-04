# Makefile

TARGET=sorty

SRCS=main.c sort_utils.c

CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g -O0

all: $(TARGET)

$(TARGET): $(SRCS)
	@echo "Building $(TARGET)..."
	@if [ -f $(TARGET) ]; then \
		echo "Removing old binary..."; \
		rm -f $(TARGET); \
	fi
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)
	@echo "Build complete"

clean:
	rm -f $(TARGET)
	@echo "Cleaned"

.PHONY: all clean

# visualizer: $(CC) visualizer.c $(CFLAGS) -lSDL3 -o visualizer
#
# default:
# 	$(CC) visualizer.c $(CFLAGS) -o sort
# 	# rm sort && $(CC) visualizer.c $(CFLAGS) -o sort
