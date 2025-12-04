#include <stdio.h>

// #include "sortutil.h"

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printverify(int arr[], const int sortedarr[], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == sortedarr[i]) {
            count++;
        }
        // printf("%d:%d\n", arr[i], sortedarr[i]);
    }
    if (count == n) printf("Success\n");
}

void printverifyVerbose(int arr[], const int sortedarr[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d:%d\n", arr[i], sortedarr[i]);
    }
}
