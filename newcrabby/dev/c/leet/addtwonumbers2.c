#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

// struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
void addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int* store = calloc(100, sizeof(int));
    int i = 0;
    int c1 = 0, c2 = 0;
    struct ListNode* cur = l1;
    while (cur) {
        store[i++] = cur->val;
        cur = cur->next;
    }
    c1 = i;
    cur = l2;
    i = 0;
    while (cur) {
        store[i++] += cur->val;
        cur = cur->next;
    }
    c2 = i;
    if (c1 > c2) i = c1;
    else i = c2;
    for (int x = 0; x < i; x++) {
        if (store[x] >= 10) {
            int overflow = store[x] - 10;
            printf("x: %d overflow: %d x+1: %d\n", store[x], overflow, store[x+1]);
            store[x + 1] += 1;
            store[x] = overflow;
        }
    }
    for (int x = 0; x < i; x++) printf("%d ", store[x]);
    printf("\n");
    free(store);
}

struct ListNode* Init(int val) {
    struct ListNode* new = malloc(sizeof(struct ListNode));
    new->val = val;
    new->next = NULL;
    return new;
}

void AddNode(struct ListNode* node, int val) {
    struct ListNode* add = Init(val);
    if (node->next == NULL) {
        node->next = malloc(sizeof(struct ListNode*));
        node->next = add;
    } else {
        struct ListNode* cur = node->next;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = malloc(sizeof(struct ListNode*));
        cur->next = add;
    }
}
void FreeNodes(struct ListNode* node) {
    struct ListNode* cur = node->next;
    free(node->next);
    free(node);
    while (cur->next != NULL) {
        struct ListNode* next = cur->next;
        free(cur->next);
        free(cur);
        cur = next;
    }
    free(cur->next);
    free(cur);
}

int main(void) {
    struct ListNode* l1 = Init(9);
    struct ListNode* l12 = Init(9);
    struct ListNode* l13 = Init(9);
    struct ListNode* l14 = Init(9);
    struct ListNode* l15 = Init(9);
    struct ListNode* l16 = Init(9);
    struct ListNode* l17 = Init(9);
    l1->next = l12;
    l12->next = l13;
    l13->next = l14;
    l14->next = l15;
    l15->next = l16;
    l16->next = l17;
    struct ListNode* l2 = Init(9);
    struct ListNode* l22 = Init(9);
    struct ListNode* l23 = Init(9);
    struct ListNode* l24 = Init(9);
    l2->next = l22;
    l22->next = l23;
    l23->next = l24;
    addTwoNumbers(l1, l2);
    free(l1);
    free(l12);
    free(l13);
    free(l14);
    free(l15);
    free(l16);
    free(l17);
    free(l2);
    free(l22);
    free(l23);
    free(l24);
    return 0;
}
