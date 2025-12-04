#include <stdio.h>
#include "../include/searchsort.h"

int main() {
    int arrs[] = {1, 2, 3, 9, 11, 13, 17, 25, 57, 90};
    int arr[] = {11, 2, 9, 13, 57, 25, 17, 1, 90, 3};
    int i;
    for (i = 0; i < 10; i++) printf("%d   ", arr[i]);
    printf("\n");
    HeapSort(arr, 10);
    // InsertionSort(arr, 10);
    // SelectionSort(arr, 10);
    // BinaryTreeSort(arr, 10);
    for (i = 0; i < 10; i++) printf("%d   ", arr[i]);
    printf("\n");
    return 0;
}
