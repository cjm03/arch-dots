#ifndef COUNTER_H
#define COUNTER_H

#include <stddef.h>

#ifdef MEMDEBUG
    #define memAlloc(file, line, size) \
        memDebugAlloc(file, line, size)
    #define memFree(file, line, ptr, size) \
        memDebugFree(file, line, ptr, size)
    #define memFreeString(file, line, ptr) \
        memDebugFreeString(file, line, ptr)
    #define memRealloc(file, line, ptr, size_old, size_new) \
        memDebugRealloc(file, line, ptr, size_old, size_new)
#else
    #define memAlloc(file, line, size) \
        memRealAlloc(file, line, size)
    #define memFree(file, line, ptr, size) \
        memRealFree(file, line, ptr, size)
    #define memFreeString(file, line, ptr) \
        memRealFreeString(file, line, ptr)
    #define memRealloc(file, line, ptr, size_old, size_new) \
        memRealRealloc(file, line, ptr, size_old, size_new)
#endif

void* memDebugAlloc(const char* file, int line, size_t size);
void memDebugFree(const char* file, int line, void* ptr, size_t size);
void memDebugFreeString(const char* file, int line, void* ptr);
void* memDebugRealloc(const char* file, int line, void* ptr, int size_old, int size_new);

void* memRealAlloc(size_t size);
long int memCheck();
void memRealFree(void* ptr, size_t size);
void memRealFreeString(char* ptr);
void* memRealRealloc(void* ptr, size_t size_old, size_t size_new);

void* memSet(void* ptr, int value, size_t size);

#endif // COUNTER_H
