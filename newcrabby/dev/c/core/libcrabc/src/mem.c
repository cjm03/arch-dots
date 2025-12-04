// mem.c - Memory Arenas

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include "../include/mem.h"

int IsPowerOfTwo(size_t x) {

    if ((x & (x - 1)) == 0) return 1;
    else return 0;
}

size_t AlignForward(size_t type, size_t alignment) {

    size_t p, a, mod;
    int ret = IsPowerOfTwo(alignment);
    if (ret != 1) exit(EXIT_FAILURE);
    p = type;
    a = alignment;
    mod = p & (a - 1);
    if (mod != 0) p += a - mod;
    return p;
}

void ArenaInitSized(M_Arena* arena, size_t capacity) {

    memset(arena, 0, sizeof(M_Arena));
    arena->base = mmap(NULL, capacity, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    arena->capacity = capacity;
    arena->offset = 0;
}

void ArenaInit(M_Arena* arena) {

    memset(arena, 0, sizeof(M_Arena));
    arena->base = mmap(NULL, M_ARENA_DEFAULT, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    arena->capacity = M_ARENA_DEFAULT;
    arena->offset = 0;
}

void* ArenaAlloc(M_Arena* arena, size_t size) {

    void* memory = 0;
    size_t aligned = AlignForward(size, DEFAULT_ALIGNMENT);
    if (arena->offset + aligned >= arena->capacity) return NULL;
    mprotect(arena->base + arena->offset, aligned, PROT_READ | PROT_WRITE);
    memory = arena->base + arena->offset;
    arena->offset += aligned;
    printf("|Arena| %zu / %zu\n", arena->offset, arena->capacity);
    return memory;
}

size_t ArenaGetMarker(M_Arena* arena) {

    return arena->offset;
}

void ArenaRestoreToMarker(M_Arena* arena, size_t marker) {

    if (marker >= arena->offset) exit(EXIT_FAILURE);
    arena->offset = marker;
    printf("|Arena| %zu / %zu\n", arena->offset, arena->capacity);
}

void ArenaClear(M_Arena* arena) {

    arena->offset = 0;
}

void ArenaFree(M_Arena* arena) {

    if (arena->base) munmap(arena->base, arena->capacity);
    arena->base = NULL;
    arena->capacity = 0;
    arena->offset = 0;
}
