#include "zutil.h"

int main(void)
{
    int def[8] = { 3, 7, 1, 6, 2, 4, 8, 5 };
    int arr8[8] = { 3, 7, 1, 6, 2, 4, 8, 5 };
    int n = sizeof(arr8) / sizeof(arr8[0]);
    uprint(arr8, n);
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && arr8[j] < arr8[j - 1]; j--) {
            swap(&arr8[j], &arr8[j - 1]);
            cprint(arr8, def, n);
            swap(&def[j], &def[j - 1]);
            uprint(arr8, n);
        }
    }

    // int arr16[16] = { 3, 11, 15, 9, 7, 1, 6, 14, 2, 4, 13, 12, 16, 8, 5, 10 };
    // int n = sizeof(arr16) / sizeof(arr16[0]);
    // for (int i = 1; i < n; i++) {
    //     for (int j = i; j > 0 && arr16[j] < arr16[j - 1]; j--) {
    //         swap(&arr16[j], &arr16[j - 1]);
    //         uprint(arr16, n);
    //     }
    // }

    return 0;
}
