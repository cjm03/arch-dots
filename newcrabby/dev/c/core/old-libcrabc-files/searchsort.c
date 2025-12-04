#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/searchsort.h"

void SWAP(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// ###
// ### SEARCH
// ###

int BinarySearch(int arr[], int n, int target) {
    clock_t begin = clock();
    int lower, upper, mid;
    lower = 0;
    upper = n;
    while (lower <= upper) {
        mid = (lower + upper) / 2;
        if (target == arr[mid]) {
            clock_t end = clock();
            double ts = (double)(end-begin) / CLOCKS_PER_SEC;
            printf("EXECUTION: %f\n", ts);
            return mid;
        }
        if (target > arr[mid]) lower = mid + 1;
        if (target < arr[mid]) upper = mid - 1;
    }
    clock_t end = clock();
    double ts = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("EXECUTION: %f\n", ts);
    return -1;
}
int RecursiveBinarySearch(int arr[], int target, int lower, int upper) {
    clock_t begin = clock();
    int mid;
    if (lower <= upper) {
        mid = (lower + upper) / 2;
        if (target == arr[mid]) {
            clock_t end = clock();
            double ts = (double)(end-begin) / CLOCKS_PER_SEC;
            printf("EXECUTION: %f\n", ts);
            return mid;
        }
        if (target > arr[mid]) lower = mid + 1;
        if (target < arr[mid]) upper = mid - 1;
        return RecursiveBinarySearch(arr, target, lower, upper);
    }
    return -1;
}

// ###
// ### SORT
// ###

void InsertionSort(int arr[], int n) {
    clock_t begin = clock();
    int i = 1;
    int j;
    while (i < n) {
        j = i;
        while (j > 0) {
            if (arr[j] < arr[j - 1]) SWAP(&arr[j - 1], &arr[j]);
            j--;
        }
        i++;
    }
    clock_t end = clock();
    double ts = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("EXECUTION: %f\n", ts);
}

void SelectionSort(int arr[], int n) {
    clock_t begin = clock();
    int i, j, sid;
    for (i = 0; i < n - 1; i++) {
        sid = i;
        for (j = n - 1; j > i; j--) {
            if (arr[sid] > arr[j]) sid = j;
        }
        SWAP(&arr[sid], &arr[j]);
    }
    clock_t end = clock();
    double ts = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("EXECUTION: %f\n", ts);
}
void BinaryTreeSort(int arr[], int n) {
    clock_t begin = clock();
    BTreeNode* bt = NULL;
    int i;
    for (i = 0; i < n; i++) BTreeNodeInsert(&bt, arr[i]);
    i = 0;
    BTreeInorder(bt, arr, &i);
    clock_t end = clock();
    double ts = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("EXECUTION: %f\n", ts);
}
void BTreeNodeInsert(BTreeNode** x, int data) {
    if (*x == NULL) {
        *x = (BTreeNode*)malloc(sizeof(BTreeNode));
        (*x)->lchild = NULL;
        (*x)->data = data;
        (*x)->rchild = NULL;
    } else {
        if (data < (*x)->data) BTreeNodeInsert(&((*x)->lchild), data);
        else BTreeNodeInsert(&((*x)->rchild), data);
    }
}
void BTreeInorder(BTreeNode* x, int arr[], int* p) {
    if (x != NULL) {
        BTreeInorder(x->lchild, arr, p);
        arr[*p] = x->data;
        *p = *p + 1;
        BTreeInorder(x->rchild, arr, p);
    }
}

void HeapSort(int arr[], int n) {
    clock_t begin = clock();
    int i, t;
    for (i = n / 2 - 1; i >= 0; i--) Heapify(arr, n, i);
    for (i = n - 1; i >= 0; i--) {
        t = arr[0];
        arr[0] = arr[i];
        arr[i] = t;
        Heapify(arr, i, 0);
    }
    clock_t end = clock();
    double ts = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("EXECUTION: %f\n", ts);
}
void Heapify(int arr[], int n, int i) {
    int largest, lch, rch, t = 0;
    lch = 2 * i + 1;
    rch = 2 * i + 2;
    if (lch >= n) return;
    largest = i;
    if (lch < n && arr[lch] > arr[largest]) largest = lch;
    if (rch < n && arr[rch] > arr[largest]) largest = rch;
    if (largest != i) {
        t = arr[i];
        arr[i] = arr[largest];
        arr[largest] = t;
        Heapify(arr, n, largest);
    }
}











