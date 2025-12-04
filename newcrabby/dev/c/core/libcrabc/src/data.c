#include <stdio.h>
#include <stdlib.h>

#include "../include/data.h"


void AddNodeFront(Node** n, int data) {
    Node* temp = malloc(sizeof(Node));
    temp->data = data;
    temp->link = *n;
    *n = temp;
}
void AddNodeMiddle(Node* n, int loc, int data) {
    Node* temp = n;
    int i;
    for (i = 0; i < loc; i++) {
        temp = temp->link;
        if (temp == NULL) {
            fprintf(stderr, "There are less than %d elements in the list\n", loc);
            return;
        }
    }
    Node* new = malloc(sizeof(Node));
    new->data = data;
    new->link = temp->link;
    temp->link = new;
}
void AddNodeEnd(Node** n, int data) {
    Node* temp;
    if (*n == NULL) {
        temp = malloc(sizeof(Node));
        temp->data = data;
        temp->link = NULL;
        *n = temp;
    } else {
        temp = *n;
        while (temp->link != NULL) temp = temp->link;
        Node* new = malloc(sizeof(Node));
        new->data = data;
        new->link = NULL;
        temp->link = new;
    }
}
void Reverse(Node** n) {
    Node* a = *n;
    Node* b = NULL;
    Node* c;
    while (a != NULL) {
        c = b;
        b = a;
        a = a->link;
        b->link = c;
    }
    *n = b;
}
void Concatenate(Node* a, Node* b) {
    if (a == NULL || b == NULL) return;
    Node* temp = a;
    while (temp->link != NULL) temp = temp->link;
    temp->link = b;
}
int Compare(Node* a, Node* b) {
    int flag;
    if (a == NULL && b == NULL) flag = 1;
    else {
        if (a == NULL || b == NULL) flag = 0;
        if (a->data != b->data) flag = 0;
        else flag = Compare(a->link, b->link);
    }
    return (flag);
}
void Copy(Node* a, Node** b) {
    if (a != NULL) {
        *b = (Node*)malloc(sizeof(Node));
        (*b)->data = a->data;
        (*b)->link = NULL;
        Copy(a->link, &((*b)->link));
    }
}
void DisplayNodes(Node* n) {
    while (n != NULL) {
        printf("%d ", n->data);
        n = n->link;
    }
    printf("\n");
}
int CountNodes(Node* n) {
    int c = 0;
    while (n != NULL) {
        n = n->link;
        c++;
    }
    return c;
}
void DeleteNode(Node** n, int data) {
    Node* temp = *n;
    Node* prev = NULL;
    while (temp != NULL) {
        if (temp->data == data) {
            if (temp == *n) *n = temp->link;
            else prev->link = temp->link;
            free(temp);
            return;
        } else {
            prev = temp;
            temp = temp->link;
        }
    }
    fprintf(stderr, "Element %d not found\n", data);
}
void FreeList(Node* n) {
    Node* cur;
    while (n != NULL) {
        cur = n;
        n = n->link;
        free(cur);
    }
}
void FreeAndPrintList(Node* n) {
    Node* cur;
    while (n != NULL) {
        cur = n;
        printf("%d ", cur->data);
        n = n->link;
        free(cur);
    }
}

// ###
// ### Doubly Linked Lists
// ###

void D_AddNodeFront(DNode** dn, int data) {
    DNode* new = (DNode*)malloc(sizeof(DNode));
    new->prev = NULL;
    new->data = data;
    new->next = *dn;
    (*dn)->prev = new;
    *dn = new;
}
void D_AddNodeMiddle(DNode* dn, int loc, int data) {
    DNode* temp = NULL;
    int i;
    for (i = 0; i < loc; i++) {
        dn = dn->next;
        if (dn == NULL) {
            fprintf(stderr, "less than %d elements\n", loc);
            return;
        }
    }
    dn = dn->prev;
    temp = (DNode*)malloc(sizeof(DNode));
    temp->data = data;
    temp->prev = dn;
    temp->next = dn->next;
    temp->next->prev = temp;
    dn->next = temp;
}
void D_AddNodeEnd(DNode** dn, int data) {
    DNode* new = NULL;
    DNode* cur = *dn;
    if (*dn == NULL) {
        *dn = (DNode*)malloc(sizeof(DNode));
        (*dn)->data = data;
        (*dn)->prev = NULL;
        (*dn)->next = NULL;
    } else {
        while (cur->next != NULL) cur = cur->next;
        new = (DNode*)malloc(sizeof(DNode));
        new->data = data;
        new->next = NULL;
        new->prev = cur;
        cur->next = new;
    }
}
void D_DisplayNodes(DNode* dn);
void D_CountNodes(DNode* dn);
void D_DeleteNode(DNode** dn, int data);
void D_FreeList(DNode* dn);

























