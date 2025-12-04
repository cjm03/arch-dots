
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "counter.h"

long int memorycounter = 0;



void* memDebugAlloc(const char* file, int line, size_t size)
{
    fprintf(stderr, "alloc  %5zu (%s, line %d)\n", size, file, line);
    return memRealAlloc(size);
}


void memDebugFree(const char* file, int line, void* ptr, size_t size)
{
    fprintf(stderr, "alloc  %5zu (%s, line %d)\n", size, file, line);
    memRealFree(ptr, size);
}

void memDebugFreeString(const char* file, int line, void* ptr)
{
    if (ptr) {
        fprintf(stderr, "free   %5zu (%s, line %d)\n", strlen(ptr) + 1, file, line);
    }
    memRealFreeString(ptr);
}

void* memDebugRealloc(const char* file, int line, void* ptr, int size_old, int size_new)
{
    if (size_old) {
        fprintf(stderr, "rfree  %5d (%s, line, %d)\n", size_old, file, line);
    }
    fprintf(stderr, "ralloc %5d (%s, line %d)\n", size_new, file, line);
    return memRealRealloc(ptr, size_old, size_new);
}

void* memRealAlloc(size_t size)
{
    void* ptr;
    ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "out of memory error - tried to allocate %lu byte.\n", size);
        exit(1);
    }
    memorycounter += size;
    return ptr;
}

long int memCheck(void)
{
    return memorycounter;
}

void memRealFree(void* ptr, size_t size)
{
    if (!ptr) return;
    memorycounter -= size;
    memSet(ptr, 0, size);
    free(ptr);
}

void memRealFreeString(char* ptr)
{
    if (!ptr) return;
    memRealFree(ptr, strlen(ptr) + 1);
}

void* memRealRealloc(void* ptr, size_t size_old, size_t size_new)
{
    ptr = realloc(ptr, size_new);
    if (!ptr) {
        fprintf(stderr, "out of memory error - tried to allocate %lu byte.\n", size_new);
        exit(1);
    }
    memorycounter -= size_old;
    memorycounter += size_new;
    return ptr;
}

void* memSet(void* ptr, int value, size_t size)
{
    volatile char* p = ptr;
    while (size--) {
        *p++ = value;
    }
    return ptr;
}
