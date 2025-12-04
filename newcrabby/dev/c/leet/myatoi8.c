#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>

int myAtoi(char* s) {
    long long r = 0;
    int neg = 1;
    while (*s == ' ') {
        s++;
    }

    if (*s == '+' || *s == '-') {
        if (*s == '-') neg = -1;
        s++;
    }
    while (isdigit((unsigned char)*s)) {
        int digit = *s - '0';
        if (r > INT_MAX / 10 || (r == INT_MAX / 10 && digit > (neg == 1 ? 7 : 8))) {
            return (neg == 1) ? INT_MAX : INT_MIN;
        }
        r = r * 10 + digit;
        s++;
    }
    return (int)(neg * r);
}

int main(void) {
    char a[] = "1337c0d3";
    int aa = myAtoi(a);
    printf("%d\n", aa);
    return 0;
}
