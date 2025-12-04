#include "zutil.h"

int main(void)
{
    int def[8] = {3, 7, 1, 6, 2, 4, 8, 5 };
    int arr8[8] = { 3, 7, 1, 6, 2, 4, 8, 5 };
    int n = sizeof(arr8) / sizeof(arr8[0]);
    uprint(arr8, n);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 1; j < n - i; j++) {
            if (arr8[j - 1] > arr8[j]) {
                swap(&arr8[j], &arr8[j - 1]);
                cprint(arr8, def, n);
                swap(&def[j], &def[j - 1]);
            }
        }
    }
    return 0;
}
