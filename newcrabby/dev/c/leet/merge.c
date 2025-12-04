#include <stdio.h>
#include <stdlib.h>

double median(int* nums1, int n1, int* nums2, int n2) {
    int n = n1 + n2;
    int* new = malloc(sizeof(int) * n);
    int i = 0, j = 0, mi;
    for (mi = 0; mi < n; mi++) {
        if (i >= n1 || j >= n2) break;
        if (nums1[i] < nums2[j]) new[mi] = nums1[i++];
        else new[mi] = nums2[j++];
    }
    while (i < n1) new[mi++] = nums1[i++];
    while (j < n2) new[mi++] = nums2[j++];
    for (i = 0; i < n; i++) printf("%d ", new[i]);
    free(new);
    return (double)n;
}

int main() {
    int a[6] = {1, 3, 5, 7, 9, 11};
    int b[6] = {2, 4, 6, 8, 10, 12};
    double ret = median(a, 6, b, 6);
    printf("%lf\n", ret);
    return 0;
}
