// stdstr.c - String Functions for Barebones C

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../include/stdstr.h"

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
