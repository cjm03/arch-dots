#include <stdio.h>
#include "sort_utils.h"

/////////////////////////////////////////////////////////////////
///
///   Bubble Sort
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = n - 1; j > i; j--) {
            if (arr[j - 1] > arr[j]) swap(&arr[j - 1], &arr[j]);
        }
    }
}

/////////////////////////////////////////////////////////////////
///
///   Insertion Sort
void insertionSort(int arr[], int n)
{
    int i = 1;
    int j;
    while (i < n) {
        j = i;
        while (j > 0) {
            if (arr[j] < arr[j - 1]) {
                swap(&arr[j - 1], &arr[j]);
            }
            j--;
        }
        i++;
    }
}

/////////////////////////////////////////////////////////////////
///
///   Selection Sort
void selectionSort(int arr[], int n)
{
    int i, j, sid;
    for (i = 0; i < n - 1; i++) {
        sid = i;
        for (j = n - 1; j > i; j--) {
            if (arr[sid] > arr[j]) {
                sid = j;
            }
        }
        swap(&arr[sid], &arr[j]);
    }
}

////////////////////////////////////////////////////////////////
///  
///  Shell Sort
void insertionModified(int arr[], int n, int incr)
{
    for (int i = incr; i < n; i += incr) {
        for (int j = i; j >= incr && arr[j - incr] > arr[j]; j -= incr) {
            swap(&arr[j - incr], &arr[j]);
        }
    }
}

void shellSort(int arr[], int n)
{
    int i, j;
    for (i = n / 2; i > 2; i /= 2) {
        for (j = 0; j < i; j++) {
            insertionModified(&arr[j], n - j, i);
        }
    }
    insertionModified(arr, n, 1);
}

/////////////////////////////////////////////////////////////////
///
///

// int main(int argc, char* argv[])
int main(void)
{
    int arr[] = {
        1690, 5555, 9868, 7593, 7060, 1048, 6667, 5319, 358, 6317, 
        8188, 4171, 9018, 9404, 9787, 7024, 5177, 9839, 2254, 9745, 
        9279, 2825, 4302, 4099, 3129, 7534, 7001, 5835, 8368, 6164, 
        783, 4657, 1273, 2440, 1405, 7284, 7592, 3239, 8346, 2474, 
        8573, 4975, 172, 9085, 3335, 1769, 7294, 9561, 1314, 1917
    };

    int n = sizeof(arr) / sizeof(arr[0]);

    // bubbleSort(arr, n);

    // selectionSort(arr, n);
    
    // insertionSort(arr, n);
    
    shellSort(arr, n);
    printverify(arr, sortedArr, n);
    return 0;
}
