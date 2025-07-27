#include <stdio.h>

int main(void)
{
    int a = 3;
    int b = 5;
    printf("a = %d\nb = %d\n", a, b);
    a = a + b;
    b = a - b;
    a = a - b;
    printf("SWAP\n");
    printf("a = %d\nb = %d\n", a, b);
    return 0;
}
