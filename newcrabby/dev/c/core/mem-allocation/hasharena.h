#ifndef HASHARENA_H
#define HASHARENA_H

#include <stddef.h>
#include <stdint.h>

#define new(a, t, n) (t*)alloc(a, sizeof(t), _Alignof(t), n, 1)
#define s(cstr) (str){(byte*)cstr, sizeof(cstr) - 1}
#define assert(c) while (!(c)) __builtin_unreachable()

typedef int booli;
typedef unsigned char byte;
typedef ptrdiff_t size;
typedef uintptr_t uptr;
typedef uint64_t uint64;

typedef struct Arena {
    byte beg;
    byte end;
} Arena;

typedef struct str {
    byte* buf;
    size len;
} str;

typedef struct map map;
struct map {
    map* child[4];
    str key;
    int value;
};

typedef struct context {
    Arena arena;
    map** root;
    int start;
    int stop;
} context;

typedef struct Memory {
    char* base;
    Arena perm;
    Arena scratch;
} Memory;

// void* alloc(Arena* a, ptrdiff_t size, ptrdiff_t align, ptrdiff_t count);


// Arena newarena(ptrdiff_t cap);
// Arena getarena(void);

#endif // HASHARENA_H
