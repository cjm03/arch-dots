#include <stdio.h>
#include "sort_utils.h"

int main(void)
{

    int arr[] = {1690, 5555, 9868, 7593, 7060, 1048, 6667, 5319, 358, 6317, 
                 8188, 4171, 9018, 9404, 9787, 7024, 5177, 9839, 2254, 9745, 
                 9279, 2825, 4302, 4099, 3129, 7534, 7001, 5835, 8368, 6164, 
                 783, 4657, 1273, 2440, 1405, 7284, 7592, 3239, 8346, 2474, 
                 8573, 4975, 172, 9085, 3335, 1769, 7294, 9561, 1314, 1917
    };
    int n = sizeof(arr) / sizeof(arr[0]);
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

    printverify(arr, sortedArr, n);

    return 0;
}
