#include <stdio.h>

int main(void)
{
    int arr[] = { 2, 8, 5, 3, 1, 10, 5, 9 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int i, j, temp;
    for (i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    for (i = 1; i < n; i++) {
        j = i;
        while (j > 0 && arr[j - 1] > arr[j]) {
            temp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = temp;
            j--;
        }
    }
    for (i = 0; i < n; i++) printf("%d ", arr[i]);
    return 0;
}
