#include <stdio.h>
#include <math.h>

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void uprint(int arr[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%02d ", arr[i]);
    }
    printf("\n");
}

void Fuprint(int arr[], int n)
{
    // printf("-------------------------------------\n|");
    for (int i = 0; i < n; i++) {
        printf("%02d|", arr[i]);
    }
    printf("\n");
    // printf("\n-------------------------------------\n");
}

void cprint(int arr[], int def[], int n)
{
    for (int i = 0; i < n; i++) {
        if (arr[i] != def[i]) {
            printf("\033[0;31m%02d \033[0m", arr[i]);
        } else {
            printf("%02d ", arr[i]);
        }
    }
    printf("\n");
}

void Fcprint(int arr[], int def[], int n)
{
    // printf("-------------------------------------\n|");
    for (int i = 0; i < n; i++) {
        if (arr[i] != def[i]) {
            printf("\033[0;31m%02d\033[0m|", def[i]);
        } else {
            printf("%02d|", arr[i]);
        }
    }
    printf("\n");
    // printf("\n-------------------------------------\n");
}

int subsets(int n)
{
    int i, inc;
    for (i = 1; i < 9; i++) {
        inc = pow(2, i);
        if (inc >= n) {
            inc = pow(2, i - 1);
            return inc;
        }

    }
    return 0;
}
