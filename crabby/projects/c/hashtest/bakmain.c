#include <stdio.h>

#include "hashtable.h"
#include "prime.h"

int main(void)
{
    printf("Init Table\n");
    Table* t = createTable();
    printf("Table Created\n\n");
    printf("Loading Clips Into Table...\n");
    loadClipsFromDir(t, "/data/mp4/rust");
    printf("Clips Loaded From Directory\n\n");
    printTable(t);
    return 0;
}
