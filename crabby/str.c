#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ITEMS 6

typedef struct Discount {
    float* orig;
    float* disc;
    float* newp;
} Discount;

Discount* create(void)
{
    Discount* t = malloc(sizeof(Discount));
    t->orig = calloc(ITEMS, sizeof(float));
    t->disc = calloc(ITEMS, sizeof(float));
    t->newp = calloc(ITEMS, sizeof(float));
    return t;
}

void parse(Discount* t)
{

}

int main(void)
{
    char* data = "item1=11.99&item2=12.99&item3=13.99&item4=14.99&item5=15.99&item6=16.99";
    printf("%lu : * %lu\n", sizeof(float), sizeof(float*));
    return 0;
}
