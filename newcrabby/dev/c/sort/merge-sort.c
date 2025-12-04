/*
 * a,b,c,d,e,f,g,h
 * a,b,c,d e,f,g,h
 * a,b c,d e,f g,h
 * a b c d e f g h
 *
 *
*/

#include <stdio.h>

void merge(int arr[], int start, int middle, int end)
{
    int i, j, k;
    int n1 = middle - start + 1;
    int n2 = end - middle;

    int lArr[n1], rArr[n2];

    for (i = 0; i < n1; i++) {
        lArr[i] = arr[start + i];
    }
    for (j = 0; j < n2; j++) {
        rArr[j] = arr[middle + 1 + j];
    }
    i = 0;
    j = 0;
    k = start;
    while (i < n1 && j < n2) {
        if (lArr[i] <= rArr[j]) {
            arr[k] = lArr[i];
            i++;
        } else {
            arr[k] = rArr[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = lArr[i];
        i++;
        k++;
    }
}

void mergesort(int arr[], int start, int end)
{
    printf("S: %d E: %d ", start, end);
    if (start < end) {
        int middle = start + (end - start) / 2;
        printf("M: %d\n", middle);
        mergesort(arr, start, middle);
        printf("1st\n");
        mergesort(arr, middle + 1, end);
        printf("2nd\n");

        printf("DONE\n");
        // merge(arr, start, middle, end);
    }
    printf("EXITED WITH: %d %d\n", start, end);
}

int main(void)
{
    int arr[] = { 2, 8, 5, 3, 9, 4, 1, 7 };
    int n = sizeof(arr) / sizeof(arr[0]);

    mergesort(arr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}
