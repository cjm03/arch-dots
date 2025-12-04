#include <stdio.h>
#include <stdlib.h>

int* countBits(int n, int* returnSize) {
    int* arr = (int*)malloc((n + 1) * sizeof(int));
    *returnSize = n + 1;
    arr[0] = 0;
    for (int i = 1; i <= n; i++) {
        arr[i] = arr[i / 2] + (i % 2);
    }
    return arr;
}

int main(void) {
    int ret = 0;
    int* pret = &ret;
    int* new = countBits(12, pret);
    printf("GOT NEW\n");
    for (int i = 0; i < ret; i++) {
        printf("%d, ", new[i]);
    }
    free(new);
    return 0;
}
