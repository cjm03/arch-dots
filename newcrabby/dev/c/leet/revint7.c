#include <stdio.h>

int reverse(int x) {
    int neg = 0, mod = 0;
    long xl = (long)x;
    long r = 0;
    if (xl < 0) {
        xl = xl * -1;
        neg = 1;
    }
    while (xl > 0) {
        r = r * 10;
        mod = xl % 10;
        r = r + mod;
        xl = xl / 10;
        printf("r: %ld\nx: %ld\n\n", r, xl);
    }
    mod = r;
    if (mod < r) return 0;
    if (neg == 1) r = r * -1;
    return (int)r;
}

int main(void) {
    int a = 1534236469;
    int b = 120;
    int c = -2147483648;
    int aa = reverse(a);
    int bb = reverse(b);
    int cc = reverse(c);
    printf("%d -> %d\n", a, aa);
    printf("%d -> %d\n", b, bb);
    printf("%d -> %d\n", c, cc);
}
