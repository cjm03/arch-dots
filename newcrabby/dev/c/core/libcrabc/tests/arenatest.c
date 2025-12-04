#include <stdio.h>
#include <string.h>
#include "../include/mem.h"

typedef struct Vec3 {
    float x, y, z;
} Vec3;

int main(void) {

    M_Arena arena;
    ArenaInitSized(&arena, 1024);
    printf("Arena: %p\n", &arena);

    Vec3* vec = ArenaAlloc(&arena, sizeof(Vec3));
    vec->x = 1.0f; 
    vec->y = 2.0f; 
    vec->z = 3.0f;
    // printf("vec = {%.2f, %.2f, %.2f}\n", vec->x, vec->y, vec->z);
    printf("Arena->offset: %zu\n", arena.offset);
    printf("Vec: %p\nsize: %zu\n", &vec, AlignForward(sizeof(Vec3), DEFAULT_ALIGNMENT));

    int* arr = ArenaAlloc(&arena, sizeof(int) * 100);
    for (int i = 0; i < 100; ++i) arr[i] = i * i;
    // printf("arr[10] = %d, arr[99] = %d\n", arr[10], arr[99]);
    printf("Arena->offset: %zu\n", arena.offset);
    printf("arr: %p - %p\nsize: %zu\n", &arr[0], &arr[99], AlignForward(sizeof(int), DEFAULT_ALIGNMENT));

    size_t mark = ArenaGetMarker(&arena);
    printf("MARKER: %zu\n", mark);
    printf("Arena->offset: %zu\n", arena.offset);
    char* temp = ArenaAlloc(&arena, sizeof(char) * 256);
    strcpy(temp, "temporary buffer");

    ArenaRestoreToMarker(&arena, mark);
    printf("Arena->offset: %zu\n", arena.offset);

    char* temp2 = ArenaAlloc(&arena, sizeof(char) * 32);
    strcpy(temp2, "reused");
    printf("Arena->offset: %zu\n", arena.offset);

    ArenaClear(&arena);

    Vec3* vecn = ArenaAlloc(&arena, sizeof(Vec3));
    vecn->x = 9; 
    vecn->y = 8; 
    vecn->z = 7;
    // printf("vecn = {%.0f, %.0f, %.0f}\n", vecn->x, vecn->y, vecn->z);
    printf("vecn: %p\nsize: %zu\n", &vecn, AlignForward(sizeof(Vec3), DEFAULT_ALIGNMENT));
    

    ArenaFree(&arena);
    return 0;
}
