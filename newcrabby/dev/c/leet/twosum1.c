#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* ret = malloc(sizeof(int) * *returnSize);
    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < numsSize; j++) {
            if (j == i) {
                continue;
            } else {
                if (nums[i] + nums[j] == target) {
                    ret[0] = i;
                    ret[1] = j;
                    return ret;
                }
            }
        }
    }
    *returnSize = 0;
    return NULL;
}

int main(void) {
    int ret = 0;
    int* retn = &ret;
    int arr[4] = {2, 7, 11, 15};
    int arrsize = 4;
    int* result1 = twoSum(arr, arrsize, 9, retn);
    printf("[%d, %d]\n", result1[0], result1[1]);
    free(result1);

    *retn = 0;
    int arr2[3] = {3, 2, 4};
    int narr2 = 3;
    int* result2 = twoSum(arr2, narr2, 6, retn);
    printf("[%d, %d]\n", result2[0], result2[1]);
    free(result2);

    *retn = 0;
    int arr3[2] = {3, 3};
    int narr3 = 2;
    int* result3 = twoSum(arr3, narr3, 6, retn);
    printf("[%d, %d]\n", result3[0], result3[1]);
    free(result3);

    return 0;
}
