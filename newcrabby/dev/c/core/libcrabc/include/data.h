// data.h

#ifndef DATA_H
#define DATA_H

// ###
// ###  Singly Linked List
// ###

typedef struct Node {
    int data;
    struct Node* link;
} Node;

void AddNodeFront(Node** n, int data);
void AddNodeMiddle(Node* n, int loc, int data);
void AddNodeEnd(Node** n, int data);
void Reverse(Node** n);
void Concatenate(Node* a, Node* b);
int Compare(Node* a, Node* b);
void Copy(Node* a, Node** b);
void DisplayNodes(Node* n);
int CountNodes(Node* n);
void DeleteNode(Node** n, int data);
void FreeList(Node* n);
void FreeAndPrintList(Node* n);


// ###
// ###  Doubly Linked List
// ###

typedef struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
} DNode;

void D_AddNodeFront(DNode** dn, int data);
void D_AddNodeMiddle(DNode* dn, int loc, int data);
void D_AddNodeEnd(DNode** dn, int data);
void D_DisplayNodes(DNode* dn);
void D_CountNodes(DNode* dn);
void D_DeleteNode(DNode** dn, int data);
void D_FreeList(DNode* dn);

// ###
// ###  Hash Table
// ###

#define HASH_TABLE_DEFAULT_SIZE 256
#define HASH_TABLE_PRIME_1 10837
#define HASH_TABLE_PRIME_2 11683

typedef struct HashTable {
    int base;
    int size;
    int count;
    void** items;
} HashTable;

int HashSimple(const char* identifier, const int prime, const int mod);
int HashGetHash(const char* identifier, const int mod, const int attempt);

#endif // DATA_H
