#include <stdio.h>
#include <stdlib.h>
#include "zutil.h"

int* merge(int s1[], int s2[], int ns1, int ns2)
{
    int* new = malloc((ns1 + ns2) * sizeof(int*));
    int x = 0;
    for (int i = 0; i < ns1 + ns2; i++) {
        if (s1[i] < s2[i]) {
            new[x] = s1[i];
            new[x + 1] = s2[i];
        } else {
            new[x] = s2[i];
            new[x + 1] = s1[i];
        }
        x += 2;
    }
    return new;
}

int* nmerge(int s1[], int s2[], int ns1, int ns2)
{
    int newsize = ns1 + ns2;
    int c1 = 0;
    int c2 = 0;
    int* new = malloc((ns1 + ns2) * sizeof(int*));
    while (c1 + c2 != newsize) {
        if (c1 == ns1) {
            new[c1+c2] = s2[c2];
            c2++;
        } else if (c2 == ns2) {
            new[c1+c2] = s1[c1];
            c1++;
        } else if (c1 < ns1 && s1[c1] < s2[c2]) {
            new[c1+c2] = s1[c1];
            c1++;
        } else if (c2 < ns2 && s2[c2] < s1[c1]) {
            new[c1+c2] = s2[c2];
            c2++;
        }
    }
    return new;
}

void mergesort(int arr[], int temp[], int n1, int n2)
{
    if (n1 == n2) return;
    int mid = (n1 + n2) / 2;
    mergesort(arr, temp, n1, mid);
    mergesort(arr, temp, mid + 1, n2);
    for (int i = n1; i < n2; i++) {
        temp[i] = arr[i];
    }
    int i1 = n1;
    int i2 = mid + 1;
    for (int cur = n1; cur <= n2; cur++) {
        if (i1 == mid + 1) arr[cur] = temp[i2++];
        else if (i2 > n2) arr[cur] = temp[i1++];
        else if (temp[i1] < temp[i2]) arr[cur] = temp[i1++];
        else arr[cur] = temp[i2++];
    }
}

int main(void)
{
    int arr[16] = { 12, 3, 7, 14, 16, 1, 10, 6, 13, 2, 11, 9, 15, 4, 8, 5 };
    int temp[16];
    int n = sizeof(arr) / sizeof(arr[0]);
    mergesort(arr, temp, 0, n - 1);
    uprint(arr, n);
    return 0;
}


// int arx[6] = { 12, 3, 7, 1, 10, 6 };
// int ary[6] = { 2, 11, 9, 4, 8, 5 };
// int n1 = (sizeof(arx) / sizeof(arx[0]));
// int n2 = (sizeof(ary) / sizeof(ary[0]));
// int* ss = merge(arx, ary, n1, n2);
// uprint(ss, n1 + n2);
// free(ss);
