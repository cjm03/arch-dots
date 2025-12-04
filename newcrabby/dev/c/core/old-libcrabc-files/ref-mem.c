// mem.h - Memory Arenas

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>

#include "../include/mem.h"
#include "../include/define.h"

#define DEFAULT_ALIGNMENT sizeof(void*)

// Alignment

b8 IsPowerOfTwo(uintptr_t x) {
    return (x & (x - 1)) == 0;
}

u64 AlignForwardU64(u64 ptr, u64 align) {
    u64 p, a, modulo;
    assert(IsPowerOfTwo(align));
    p = ptr;
    a = (size_t)align;
    modulo = p & (a - 1);
    if (modulo != 0) {
        p += a - modulo;
    }
    return p;
}

// Arena

void* ArenaAlloc(M_Arena* arena, u64 size) {
    void* memory = 0;
    size = AlignForwardU64(size, DEFAULT_ALIGNMENT);
    if (arena->alloc_position + size > arena->commit_position) {
        if (!arena->static_size) {
            u64 commit_size = size;
            commit_size += M_ARENA_COMMIT_SIZE - 1;
            commit_size -= commit_size % M_ARENA_COMMIT_SIZE;
            if (arena->commit_position >= arena->max) {
                assert(0 && "Arena is out of memory");
            } else {
                mprotect(arena->memory + arena->commit_position, commit_size, PROT_READ | PROT_WRITE);
                arena->commit_position += commit_size;
            }
        } else {
            assert(0 && "Static-Size Arena is out of memory");
        }
    }
    memory = arena->memory + arena->alloc_position;
    arena->alloc_position += size;
    return memory;
}

void* ArenaAllocZero(M_Arena* arena, u64 size) {
    void* result = ArenaAlloc(arena, size);
    memset(result, 0, size);
    return result;
}

void ArenaDealloc(M_Arena* arena, u64 size) {
    if (size > arena->alloc_position) {
        size = arena->alloc_position;
    }
    arena->alloc_position -= size;
}

void* ArenaAllocArraySized(M_Arena* arena, u64 elem_size, u64 count) {
    return ArenaAlloc(arena, elem_size * count);
}

void ArenaInit(M_Arena* arena) {
    memset(arena, 0, sizeof(M_Arena));
    arena->max = M_ARENA_MAX;
    arena->memory = mmap(NULL, arena->max, PROT_NONE, MAP_PRIVATE | MAP_ANON, -1, 0);
    arena->alloc_position = 0;
    arena->commit_position = 0;
    arena->static_size = false;
}

void ArenaInitSized(M_Arena* arena, u64 max) {
    memset(arena, 0, sizeof(M_Arena));
    arena->max = max;
    arena->memory = mmap(NULL, arena->max, PROT_NONE, MAP_PRIVATE | MAP_ANON, -1, 0);
    arena->alloc_position = 0;
    arena->commit_position = 0;
    arena->static_size = false;
}

void ArenaClear(M_Arena* arena) {
    ArenaDealloc(arena, arena->alloc_position);
}

void ArenaFree(M_Arena* arena) {
    munmap(arena->memory, arena->max);
}


