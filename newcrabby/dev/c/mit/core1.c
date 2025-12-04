#include <stdio.h>

int main(void) {
    for (int i = 0; i < 100; i++) {
        int tri = ((i * i) + i) / 2;
        printf("%d ", tri);
    }
    return 0;
}
