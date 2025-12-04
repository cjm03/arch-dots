#include <stdio.h>

void square(int* num) {
    *num = *num * *num; // num = num * num;
}

int main(void) {
    int x = 4;
    square(&x);         // square(x);
    printf("%d\n", x);
    return 0;
}
