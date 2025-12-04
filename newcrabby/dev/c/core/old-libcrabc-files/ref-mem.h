// mem.h
//
// Headerfile for mem.c, a program to implement a basic memory arena for quick and safe
// manangment of memory.
//
// Charlie Moye
// 11-12-2025

#ifndef MEM_H
#define MEM_H

#include "define.h"

// Arenas

typedef struct M_Arena {
    u8* memory;
    u64 max;
    u64 alloc_position;
    u64 commit_position;
    b8 static_size;
} M_Arena;

#define M_ARENA_MAX Gigabytes(1)
#define M_ARENA_COMMIT_SIZE Kilobytes(8)

void* ArenaAlloc(M_Arena* arena, u64 size);
void* ArenaAllocZero(M_Arena* arena, u64 size);
void ArenaDealloc(M_Arena* arena, u64 size);
void* ArenaAllocArraySized(M_Arena* arena, u64 elem_size, u64 count);

#define ArenaAllocArray(arena, elem_type, count) ArenaAllocArraySized(arena, sizeof(elem_type), count)

void ArenaInit(M_Arena* arena);
void ArenaInitSized(M_Arena* arena, u64 max);
void ArenaClear(M_Arena* arena);
void ArenaFree(M_Arena* arena);


#endif // MEM_H
