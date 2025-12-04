#include <stdio.h>
#include "../include/data.h"


int main(void) {
    Node* p = NULL;
    Node* q = NULL;
    AddNodeEnd(&p, 14);
    AddNodeEnd(&p, 30);
    AddNodeEnd(&p, 25);
    AddNodeFront(&p, 99);
    AddNodeFront(&p, 88);
    AddNodeMiddle(p, 3, 41);
    AddNodeMiddle(p, 5, 89);
    printf("Count: %d\n", CountNodes(p));
    DisplayNodes(p);

    AddNodeEnd(&q, 42);
    AddNodeEnd(&q, 17);
    AddNodeEnd(&q, 67);
    AddNodeFront(&q, 77);
    AddNodeFront(&q, 66);
    AddNodeMiddle(q, 2, 60);
    AddNodeMiddle(q, 4, 11);
    printf("Count: %d\n", CountNodes(q));
    DisplayNodes(q);

    DeleteNode(&p, 99);
    DeleteNode(&p, 14);
    DeleteNode(&q, 60);

    printf("Count: %d\n", CountNodes(p));
    DisplayNodes(p);

    printf("Count: %d\n", CountNodes(q));
    DisplayNodes(q);

    Reverse(&p);
    DisplayNodes(p);

    Concatenate(p, q);
    DisplayNodes(p);
    
    Node* z = NULL;
    Copy(p, &z);

    int pz = Compare(p, z);
    if (pz == 1) {
        printf("Match:\n\t");
        DisplayNodes(p);
        printf("\t");
        DisplayNodes(z);
    } else {
        printf("lists do not match\n");
    }

    FreeList(p);
    FreeList(z);

    return 0;
}
