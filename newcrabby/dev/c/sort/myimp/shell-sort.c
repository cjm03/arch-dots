#include <stdio.h>
#include "zutil.h"

int counter = 0;

void insertionsort(int def[], int subarr[], int n)
{
    int i, j;
    for (i = 1; i < n; i++) {
        for (j = i; j > 0 && subarr[j] < subarr[j - 1]; j--) {
            swap(&subarr[j], &subarr[j - 1]);
            printf("%02d | ", counter);
            cprint(subarr, def, n);
            swap(&def[j], &def[j - 1]);
            counter++;
        }
    }
}

void insertionsort2(int def[], int subarr[], int n, int start, int incr)
{
    int i, j;
    for (i = start + incr; i < n; i += incr) {
        for (j = i; (j >= incr) && subarr[j] < subarr[j - incr]; j -= incr) {
            swap(&subarr[j], &subarr[j - incr]);
            printf("%02d | ", counter);
            cprint(subarr, def, n);
            swap(&def[j], &def[j - incr]);
            counter++;
        }
    }
}

int main(void)
{
    int def[16] = { 9, 16, 3, 7, 14, 13, 1, 10, 6, 2, 11, 12, 4, 8, 5, 15 };
    int arr[16] = { 9, 16, 3, 7, 14, 13, 1, 10, 6, 2, 11, 12, 4, 8, 5, 15 };
    // int def[12] = { 20, 30, 44, 54, 55, 11, 78, 14, 13, 79, 12, 98 };
    // int arr[12] = { 20, 30, 44, 54, 55, 11, 78, 14, 13, 79, 12, 98 };
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("#  |  0  1  2  3  4  5  6  7  8  9 10 11\n");
    printf("----------------------------------------\n");
    printf("%02d | ", counter++);
    uprint(arr, n);
    for (int i = n / 2; i > 2; i /= 2) {
        for (int j = 0; j < i; j++) {
            insertionsort2(def, arr, n, j, i);
        }
    }
    insertionsort(def, arr, n);
    printf("%02d | ", counter);
    uprint(arr, n);
    return 0;
}
