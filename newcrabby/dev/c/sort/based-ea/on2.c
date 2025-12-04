#include <stdio.h>

/* helper swap function */
void swap(int* a, int* b)
{
    int x = *a;
    *a = *b;
    *b = x;
}

/* perform insertionsort on arr[], in place */
void InsertionSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n; i++) {
        j = i;
        while ((j > 0) && (arr[j] < arr[j - 1])) {
            // printf("%d %d %d %d %d %d %d %d -> ", arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7]);
            swap(&arr[j], &arr[j - 1]);
            // printf("%d %d %d %d %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7]);
            j--;
        }
    }
}

void SelectionSort(int arr[], int n)
{
    int i, j, k;
    for (i = 0; i < n - 1; i++) {
        k = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[k]) {
                k = j;
            }
        }
        swap(&arr[i], &arr[k]);
    }
}

void BubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = n - 1; j > i; j--) {
            if (arr[j - 1] > arr[j]) {
                swap(&arr[j - 1], &arr[j]);
                
            }
        }
    }
    // for (i = n; i > 1; i--) {
    //     for (j = 1; j < i - 1; j++) {
    //         if (arr[j] > arr[j + 1]) {
    //             swap(&arr[j], &arr[j + 1]);
    //         }
    //     }
    // }
}



int main(void)
{
    int arr[] = { 2, 8, 5, 3, 9, 4, 1, 7 };
    int n = sizeof(arr) / sizeof(arr[0]);

    BubbleSort(arr, n);
    // SelectionSort(arr, n);
    // InsertionSort(arr, n);

    for (int i = 0; i < n; i++) printf("%d ", arr[i]);

    return 0;
}
