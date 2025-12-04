#include <stdio.h>

int* initArray(int size)
{               // myArray IS LOCAL TO initArray() !!
    int myArray[size];
    for (int i = 0; i < size; i++) {
        myArray[i] = i;
    }
    return myArray;
}

int main(void)
{
    int* arr = initArray(32);
    printf("%d %d %d %d\n", *arr, *arr + 2, *arr + 4, *arr + 6);
    return 0;
}
