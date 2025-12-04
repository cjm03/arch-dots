#ifndef SEARCHSORT_H
#define SEARCHSORT_H

typedef struct BTreeNode {
    struct BTreeNode* lchild;
    int data;
    struct BTreeNode* rchild;
} BTreeNode;

void SWAP(int* a, int* b);

int BinarySearch(int arr[], int n, int target);
int RecursiveBinarySearch(int arr[], int target, int lower, int upper);

void InsertionSort(int arr[], int n);
void SelectionSort(int arr[], int n);

void BinaryTreeSort(int arr[], int n);
void BTreeNodeInsert(BTreeNode** x, int data);
void BTreeInorder(BTreeNode* x, int arr[], int* p);

void HeapSort(int arr[], int n);
void Heapify(int arr[], int n, int i);

#endif // SEARCHSORT_H
