#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flate.h"

#define ITEMS 6

typedef struct Discount {
    float* orig;
    float* disc;
    float* new;
    float totalcost;
    float totaldisc;
} Discount;

Discount* create(void)
{
    Discount* t = malloc(sizeof(Discount));
    t->orig = calloc(ITEMS, sizeof(float));
    t->disc = calloc(ITEMS, sizeof(float));
    t->new = calloc(ITEMS, sizeof(float));
    t->totalcost = 0.0;
    t->totaldisc = 0.0;

    for (int i = 0; i < ITEMS; i++) {
        t->orig[i] = 14.99 + (float)i;
        t->disc[i] = t->orig[i] * 0.15;
        t->new[i] = t->orig[i] - t->disc[i];
        t->totaldisc += t->disc[i];
        t->totalcost += t->new[i];
    }

    for (int k = 0; k < ITEMS; k++) {
        printf("%f\t%f\t%f\n", t->orig[k], t->disc[k], t->new[k]);
    }
    return t;
}



int main(void)
{
    Discount* t = create();

    for (int k = 0; k < ITEMS; k++) {
        printf("%f\t%f\t%f\n", t->orig[k], t->disc[k], t->new[k]);
    }

    Flate* f = NULL;

    flateSetFile(&f, "discounted.html");

    for (int i = 0; i < ITEMS; i++) {

        char* temp1 = malloc(16);
        char* temp2 = malloc(16);
        char* temp3 = malloc(16);
        if (temp1 == NULL || temp2 == NULL || temp3 == NULL) {
            perror("memory\n");
            return -1;
        }
        snprintf(temp1, 16, "%.2f", t->orig[i]);
        snprintf(temp2, 16, "%.2f", t->disc[i]);
        snprintf(temp3, 16, "%.2f", t->new[i]);
        printf("\n\t%s\n\t%s\n\t%s\n", temp1, temp2, temp3);
        flateSetVar(f, "original", temp1, NULL);
        flateSetVar(f, "discount", temp2, NULL);
        flateSetVar(f, "new", temp3, NULL);
        flateSetVar(f, "disc", "", NULL);
        flateDumpTableLine(f, "disc");
        free(temp1);
        free(temp2);
        free(temp3);
    }
    flateSetVar(f, "totaldisc", "321", NULL);
    flateSetVar(f, "totalcost", "123", NULL);
    // flatePrint(f, "text/html");
    char* buf = flatePage(f);
    flateFreeMem(f);
    free(t->orig);
    free(t->disc);
    free(t->new);
    free(t);
    size_t len = strlen(buf);
    printf("%s\n%ld\n", buf, len);
    free(buf);

    return 0;

}
