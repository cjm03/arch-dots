#include <stdio.h>
#include "zutil.h"

int main(void)
{
    int def[12] = { 12, 3, 7, 1, 10, 6, 2, 11, 9, 4, 8, 5 };
    int arr[12] = { 12, 3, 7, 1, 10, 6, 2, 11, 9, 4, 8, 5 };
    // int def[12] = { 9, 3, 7, 1, 10, 6, 2, 11, 12, 4, 8, 5 };
    // int arr[12] = { 9, 3, 7, 1, 10, 6, 2, 11, 12, 4, 8, 5 };
    int n = sizeof(arr) / sizeof(arr[0]);
    uprint(arr, n);
    for (int i = 0; i < n - 1; i++) {
        int keyidx = 0;
        for (int j = 1; j < n - i; j++) {
            if (arr[j] > arr[keyidx]) {
                keyidx = j;
            }
        }
        swap(&arr[n - i - 1], &arr[keyidx]);
        // printf("arr[%d] = %d: ", keyidx, arr[keyidx]);
        Fcprint(arr, def, n);
        swap(&def[n - i - 1], &def[keyidx]);
        // printf("            ");
        Fuprint(arr, n);
    }
    return 0;
}
