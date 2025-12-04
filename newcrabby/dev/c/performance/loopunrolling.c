#include <stdio.h>

int main(void)
{
    int sum, i, limit, rem, quot, incr, x, count;
    sum = 0;
    printf("Enter limit: ");
    scanf("%d", &limit);
    for (i = 9; i >= 1; i--) {
        rem = limit % i;
        if (rem == 0) break;
    }
    incr = i;
    count = 0;
    for (i = 1; i <= limit; i += incr) {
        x = 0;
        while (x < incr) {
            sum += i + x;
            x++;
        }
        count++;
    }
    printf("First %d sequence numbers sum is %d\n", limit, sum);
    printf("Loop executed %d times\n", count);
    return 0;
}
