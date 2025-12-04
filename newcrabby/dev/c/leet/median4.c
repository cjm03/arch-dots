// 1, 3, 7, 8
// 2, 5, 6, 9
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int newSize = nums1Size + nums2Size;
    int easy = (newSize) % 2;
    int* new = malloc(sizeof(int) * newSize);
    memcpy(new, nums1, sizeof(int) * nums1Size);
    memcpy(new + nums1Size, nums2, sizeof(int) * nums2Size);
    int i = 1, j = 0;
    while (i < newSize) {
        j = i;
        while (j > 0) {
            if (new[j] < new[j - 1]) {
                int temp = new[j];
                new[j] = new[j - 1];
                new[j - 1] = temp;
            }
            j--;
        }
        i++;
    }
    if (easy == 1) {
        double median = new[newSize / 2];
        free(new);
        return median;
    } else {
        double left = new[newSize / 2];
        double right = new[(newSize / 2) - 1];
        free(new);
        return (right + left) / 2;
    }

}

int main(void) {
    // int a[5] = {1, 2, 8, 12, 15};
    // int b[4] = {3, 4, 6, 9};
    int c[2] = {1, 2};
    int d[2] = {3, 4};
    // double ret = findMedianSortedArrays(a, 5, b, 4);
    double cd = findMedianSortedArrays(c, 2, d, 2);
    // printf("%lf\n", ret);
    printf("%lf\n", cd);
}
