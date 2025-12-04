// mem.h
// ███╗   ███╗███████╗███╗   ███╗ ██████╗ ██████╗ ██╗   ██╗
// ████╗ ████║██╔════╝████╗ ████║██╔═══██╗██╔══██╗╚██╗ ██╔╝
// ██╔████╔██║█████╗  ██╔████╔██║██║   ██║██████╔╝ ╚████╔╝ 
// ██║╚██╔╝██║██╔══╝  ██║╚██╔╝██║██║   ██║██╔══██╗  ╚██╔╝  
// ██║ ╚═╝ ██║███████╗██║ ╚═╝ ██║╚██████╔╝██║  ██║   ██║   
// ╚═╝     ╚═╝╚══════╝╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝   
//
//  Headerfile for mem.c. Contains functions for use with memory arenas.
//
//  Charlie Moye
//  11-12-2025

#ifndef MEM_H
#define MEM_H

#include <stddef.h>
#include <stdint.h>
#include "../include/define.h"

#define DEFAULT_ALIGNMENT sizeof(void*)
#define M_ARENA_DEFAULT Kilobytes(16)

typedef struct M_Arena {
    uint8_t* base;
    size_t capacity;
    size_t offset;
} M_Arena;

// Determine if x is a power of two
int IsPowerOfTwo(size_t x);

// Get the alignment for type aligned to alignment
size_t AlignForward(size_t type, size_t alignment);

// Create an arena of custom size
void ArenaInitSized(M_Arena* arena, size_t capacity);

// Create an arena of default size (16 Kilobytes);
void ArenaInit(M_Arena* arena);

// Allocate size bytes of memory in arena arena
void* ArenaAlloc(M_Arena* arena, size_t size);

// Get the current marker
size_t ArenaGetMarker(M_Arena* arena);

// Move the marker to the provided marker
void ArenaRestoreToMarker(M_Arena* arena, size_t marker);

// Clear the arena
void ArenaClear(M_Arena* arena);

// Deallocate the arena
void ArenaFree(M_Arena* arena);


#endif // MEM_H
