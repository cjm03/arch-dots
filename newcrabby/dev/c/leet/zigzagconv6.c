/*
 *  "PAYPALISHIRING" -> "PAHNAPLSIIGYIR"
 *  P   A   H   N    -> PAHN
 *  A P L S I I G    -> APLSIIG
 *  Y   I   R        -> YIR
 *
 *  00    01    02    03
 *  10 11 12 13 14 15 16 
 *  20    21    22 
 *
 *  00, 10, 20, 11, 01, 12, 21, 13, 02, 14, 22, 15, 03, 16
 *   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13
 *
 *  00 = 0, 01 = 4, 02 = 8, 03 = 12
 *  10 = 1, 11 = 3, 12 = 5, 13 =  7, 14 =  9, 15 = 11, 16 = 13
 *  20 = 2, 21 = 6, 22 = 10
*/

/*
 * "PAYPALISHIRING" -> "PINALSIGYAHRPI"
 * P     I     N
 * A   L S   I G
 * Y A   H R
 * P     I
 *
 * 00, 10, 20, 30, 21, 11, 01, 12, 22, 31, 23, 13, 02, 14
 *  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13
 *
 *  00 = 0,                 01 = 6,                  02 = 12
 *  10 = 1,         11 = 5, 12 = 7,         13 = 11, 14 = 13
 *  20 = 2, 21 = 4,         22 = 8, 23 = 10
 *  30 = 3,                 31 = 9
*/ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* oldconvert(char* s, int rows) {
    int n = strlen(s);
    char** r = calloc(rows, sizeof(char*));
    for (int i = 0; i < rows; i++) {
        r[i] = calloc(8, sizeof(char));
    }
    int x = 0;
    int y = 0;
    int z = 0;
    while (y < n) {
        for (y = 0; y < rows; y++) {
            r[y][x] = s[z++];
        }
        x++;
        for (y = y - 1; y >= 0; y--) {
            r[y][x] = s[z++];
        }
        x++;
    }
    for (int i = 0; i < rows; i++) {
        printf("%s\n", r[i]);
    }
    for (int i = 0; i < rows; i++) free(r[i]);
    free(r);
    return "hey";
}

char* convert(char* s, int rows) {
    if (rows == 1) return s;
    int len = strlen(s);
    char* r = malloc(len + 1);
    int i = 0, idx = 0;
    for (i = 0; i < rows; i++) {
        for (int j = i; j < len; j += 2 * (rows - 1)) {
            r[idx++] = s[j];
            if (i > 0 && i < rows - 1 && j + 2 * (rows - 1) - 2 * i < len) {
                r[idx++] = s[j + 2 * (rows - 1) - 2 * i];
            }
        }
    }
    r[idx] = '\0';
    return r;
}

int main(void) {
    char str[] = "PAYPALISHIRING";
    printf("3: %zu -1: %zu\n", strlen(str) / 3, strlen(str) / 2);
    printf("4: %zu -1: %zu\n", strlen(str) / 4, strlen(str) / 3);
    char* ret = convert(str, 5);
    printf("%s\n", ret);
    free(ret);
    return 0;
}
