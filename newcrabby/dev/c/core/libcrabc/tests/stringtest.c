#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../allhead.h"

int main(void)
{
    /****
     * Using Malloc
     */

    String* first = CreateString("What does the fox say?");
    String* second = CreateString("abcdefghijklmnopqrstuvwxyz0123456789");

    char* first_local = GetStringData(first);
    char* second_local = GetStringData(second);

    PrintString(first);
    PrintString(second);
    printf("first_local: %s\nSize: %zu\n", first_local, strlen(first_local));
    printf("second_local: %s\nSize: %zu\n", second_local, strlen(second_local));

    free(first_local);
    free(second_local);

    SliceString(first, 5, 12);
    String* second_dns = CreateSlicedString(second, 24, 32);

    PrintString(first);
    PrintString(second);
    PrintString(second_dns); 

    DeleteString(first);
    DeleteString(second);
    DeleteString(second_dns); 

    /****
     * Using Arenas
     */

    M_Arena arena = {0};
    ArenaInitSized(&arena, Kilobytes(16));
    char* string = "Dilapidated, delinquent, federline Jones!";

    String arenaFirst = M_CreateString(&arena, string);
    String arenaFirstSliced = M_CreateSlicedString(&arena, &arenaFirst, 18, 29);

    size_t marker = ArenaGetMarker(&arena);

    String arenaDuplicate = M_CreateString(&arena, arenaFirst.str);

    ArenaRestoreToMarker(&arena, marker);

    String arenaDuplicateSlice = M_CreateString(&arena, arenaFirstSliced.str);
    char* wimp = ArenaAlloc(&arena, sizeof(char) * 64);
    wimp = "abcdefghijklmnopqrstuvwxyz0123456789";

    PrintString(&arenaFirst);
    PrintString(&arenaFirstSliced);
    PrintString(&arenaDuplicate);
    PrintString(&arenaDuplicateSlice);
    printf("wimp: %s\n", wimp);

    StringUppercase(arenaFirst.str, arenaFirst.size);
    PrintString(&arenaFirst);

    char* getdata = M_GetStringData(&arena, &arenaDuplicate);
    printf("getdata: %s\n", getdata);

    ArenaFree(&arena);
    return 0;
}
