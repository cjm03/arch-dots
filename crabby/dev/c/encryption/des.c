#include <stdio.h>
#include <stdlib.h>

#include "des.h"

int initialPermutation[] = {58, 50, 42, 34, 26, 18, 10, 2,
                            60, 52, 44, 36, 28, 20, 12, 4,
                            62, 54, 46, 38, 30, 22, 14, 6,
                            64, 56, 48, 40, 32, 24, 16, 8,
                            57, 49, 41, 33, 25, 17,  9, 1,
                            59, 51, 43, 35, 27, 19, 11, 3,
                            61, 53, 45, 37, 29, 21, 13, 5,
                            63, 55, 47, 39, 31, 23, 15, 7};

int permutationC2[] =      {14, 17, 11, 24,  1,  5,  3, 28,
                            15,  6, 21, 10, 23, 19, 12,  4,
                            26,  8, 16,  7, 27, 20, 13,  2,
                            41, 52, 31, 37, 47, 55, 30, 40,
                            51, 45, 33, 48, 44, 49, 39, 56,
                            34, 53, 46, 42, 50, 36, 29, 32};

int fullPC1[] =            {57, 49, 41, 33, 25, 17,  9,
                            1, 58, 50, 42, 34, 26, 18,
                            10,  2, 59, 51, 43, 35, 27,
                            19, 11,  3, 60, 52, 44, 36,
                            63, 55, 47, 39, 31, 23, 15,
                            7, 62, 54, 47, 38, 30, 22,
                            14,  6, 61, 53, 45, 37, 29,
                            21, 13,  5, 28, 20, 12,  4};

int c0PC1[] =              {57, 49, 41, 33, 25, 17, 9,
                            10, 2, 59, 51, 43, 35, 27,
                            63, 55, 47, 39, 31, 23, 15,
                            14, 6, 61, 53, 45, 37, 29};

int d0PC1[] =              {1, 58, 50, 42, 34, 26, 18,
                            19, 11, 3, 60, 52, 44, 36,
                            7, 62, 54, 47, 38, 30, 22,
                            21, 13, 5, 28, 20, 12, 4};

int bitsShiftPerRound[] =              {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

void printCharAsBinary(char input)
{
    for (int i = 0; i < 8; i++) {
        char shift_byte = 0x01 << (7 - i);
        if (shift_byte & input) {
            printf("1");
        } else {
            printf("0");
        }
    }
}

void generateKey(unsigned char* key)
{
    for (int i = 0; i < 8; i++) {
        key[i] = rand() % 255;
    }
}

void printKeySet(key_set key_set)
{
    int i;
    printf("K: \n");
    for (i = 0; i < 8; i++) {
        printf("%02X : ", key_set.k[i]);
        printCharAsBinary(key_set.k[i]);
        printf("\n");
    }
    printf("\nC: \n");
    for (i = 0; i < 4; i++) {
        printf("%02X : ", key_set.c[i]);
        printCharAsBinary(key_set.c[i]);
        printf("\n");
    }
    printf("\nD: \n");
    for (i = 0; i < 4; i++) {
        printf("%02X : ", key_set.d[i]);
        printCharAsBinary(key_set.d[i]);
        printf("\n");
    }
    printf("\n");
}

void applyIP(unsigned char* binmsg, unsigned char* output, int initial_perm_table[])
{
    int pos;
    for (int i = 0; i < 64; i++) {
        pos = initial_perm_table[i];
        output[i] = binmsg[pos];
    }
}

void applyPC1(unsigned char* key, unsigned char* output, int fullPC1[])
{
    int pos;
    for (int i = 0; i < 56; i++) {
        pos = fullPC1[i];
        output[i] = key[pos];
    }
}

void splitLeftAndRight(unsigned char* postPC1, unsigned char* C0, unsigned char* D0)
{
    for (int i = 0; i < 28; i++) {
        C0[i] = postPC1[i];
        D0[i] = postPC1[i + 28];
    }
}

void leftShift(unsigned char* C0, unsigned char* D0, int round, int bitsShiftPerRound[])
{
    int shifts = bitsShiftPerRound[round];
    int cfirstbyte = C0[0];
    int dfirstbyte = D0[0];
    if ((C0 << shifts) && cfirstbyte == 1) {
        C0[27] = cfirstbyte;
    }
}

