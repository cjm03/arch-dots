#include <stdio.h>
#include <stdlib.h>

int* initArray(int size)
{
    int* myArray = malloc(sizeof(int) * size);
    if (!myArray) {
        fprintf(stderr, "malloc;; initArray()");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        myArray[i] = i;
    }
    return myArray;
}

void printArr(int* arr, int size)
{
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}

int* reallocateArray(int* arr, int incr)
{
    int* newarr = realloc(arr, incr * sizeof(int));
    if (!newarr) {
        fprintf(stderr, "realloc;; reallocateArray()");
        free(arr);
        exit(EXIT_FAILURE);
    }
    return newarr;
}
void realAr(int* new, int* arr, int incr)
{
    new = (int*)realloc(arr, incr * sizeof(int));
    if (new != NULL) {
        free(arr);
        return;
    }
}

int main(void)
{
    int elements = 67;
    int* arr = initArray(elements);
    printArr(arr, elements);

    int real = 0;

    printf("\nEnter the length youd like to increase your array by: ");
    scanf("%d", &real);
    int* new;
    // int* arr2 = reallocateArray(arr, real + elements);
    realAr(new, arr, real + elements);
    printArr(new, real);
    free(arr);
    free(new);
    return 0;
}
