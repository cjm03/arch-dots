// str.c - Custom String Library

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/mem.h"
#include "../include/str.h"

// #########################################
// ### Strings only using malloc

char* Strndup(char* buffer, size_t n) {
    char* p = malloc(n + 1);
    if (!p) return NULL;
    memcpy(p, buffer, n);
    p[n] = '\0';
    return p;
}

char* SubstringReturn(char* str, int idx1, int idx2) {
    size_t len = strlen(str);
    if (idx2 >= (int)len) return NULL;
    size_t newlen = idx2 - idx1 + 2;
    char* out = malloc(newlen * sizeof(char));
    for (int i = idx1; i < idx2 + 1; i++) out[i - idx1] = str[i];
    out[newlen - 1] = '\0';
    return out;
}

void SubstringReplace(char* str, int idx1, int idx2) {
    size_t len = strlen(str);
    if (idx2 >= (int)len) return;
    size_t newlen = idx2 - idx1 + 2;
    char* temp = Strndup(str, len);
    memset(str, 0, len);
    for (int i = idx1; i < idx2 + 1; i++) str[i - idx1] = temp[i];
    str[newlen - 1] = '\0';
    free(temp);
}

void StringUppercase(char* str, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if ('a' <= str[i] && str[i] <= 'z') {
            str[i] += 'A' - 'a';
        }
    }
}

void StringLowercase(char* str, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if ('A' <= str[i] && str[i] <= 'Z') {
            str[i] += 'a' - 'A';
        }
    }
}


// ##############################################
// ###  Strings using String structure and malloc

String* CreateString(char* string) {
    String* s = malloc(sizeof(String));
    if (s == NULL) {
        fprintf(stderr, "malloc: error allocating String\n");
        return NULL;
    }
    size_t len = strlen(string);
    s->size = len;
    s->str = malloc(len + 1);
    if (s->str == NULL) {
        fprintf(stderr, "malloc: error allocating s->str\n");
        free(s);
        return NULL;
    }
    memcpy(s->str, string, len);
    s->str[len] = '\0';
    return s;
}

String* CreateSlicedString(String* s, size_t start_idx, size_t end_idx) {
    String* new = CreateString(s->str);
    SliceString(new, start_idx, end_idx);
    return new;
}

void SliceString(String* s, size_t start_idx, size_t end_idx) {
    size_t newsize = end_idx - start_idx + 1;
    char* full = Strndup(s->str, s->size);
    ClearString(s);
    s->str = realloc(s->str, newsize + 1);
    for (size_t i = 0; i < newsize; i++) {
        s->str[i] = full[i + start_idx];
    }
    s->size = newsize;
    free(full);
}

String* DuplicateString(String* s) {
    String* new = CreateString(s->str);
    return new;
}

char* GetStringData(String* s) {
    char* temp = Strndup(s->str, s->size);
    return temp;
}

void PrintString(String* s) {
    printf("String: {%s}\nSize: {%zu}\n", s->str, s->size);
}

size_t GetStringSize(String* s) {
    return s->size;
}

void ClearString(String* s) {
    if (s == NULL) {
        fprintf(stderr, "Cannot free empty string structure\n");
        return;
    }
    if (s->str == NULL) {
        fprintf(stderr, "Cannot free empty string!\n");
        return;
    }
    memset(s->str, 0, s->size);
}

void DeleteString(String* s) {
    if (s == NULL) {
        fprintf(stderr, "Cannot free empty string structure\n");
        return;
    }
    if (s->str == NULL) {
        fprintf(stderr, "Cannot free empty string!\n");
        return;
    }
    free(s->str);
    free(s);
}

// #############################################
// ### Strings using String structure and Arenas

// Create a new string. DON'T NEED DUPLICATE FUNCTION, JUST CALL CREATE W s->str
String M_CreateString(M_Arena* arena, char* string) {
    size_t len = strlen(string);
    String s = {0};
    s.size = len;
    char* temp = ArenaAlloc(arena, len + 1);
    for (size_t i = 0; i < len; i++) {
        temp[i] = string[i];
    }
    temp[len] = '\0';
    s.str = temp;
    return s;
}

String M_CreateSlicedString(M_Arena* arena, String* s, size_t start_idx, size_t end_idx) {
    size_t newsize = end_idx - start_idx + 1;
    String new = {0};
    new.size = newsize;
    char* temp = ArenaAlloc(arena, newsize + 1);
    for (size_t i = 0; i < newsize; i++) {
        temp[i] = s->str[i + start_idx];
    }
    new.str = temp;
    return new;
}

char* M_GetStringData(M_Arena* arena, String* s) {
    char* data = ArenaAlloc(arena, s->size + 1);
    memcpy(data, s->str, s->size);
    data[s->size] = '\0';
    return data;
}















