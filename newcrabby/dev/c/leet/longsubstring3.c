#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int lengthOfLongestSubstring(char* s) {
    int max = 0, left = 0, i = 0;
    int last[256];
    for (i = 0; i < 256; i++) last[i] = -1;
    for (int right = 0; s[right] != '\0'; right++) {

        uint8_t c = s[right];
        printf("c: %c | ascii: %d\n", c, c);

        if (last[c] >= left) left = last[c] + 1;
        printf("last[c]: %d | left: %d\n", last[c], left);

        last[c] = right;
        printf("last[c]: %d | right: %d\n", last[c], right);

        int window = right - left + 1;
        printf("window: %d | max: %d\n", window, max);
        for (i = left; i < right + 1; i++) printf("%c", s[i]);
        printf("\n\n");
        if (window > max) max = window;
    }
    return max;
}

int main(void) {
    char first[] = "pwwkewabcabcbb";
    int one = lengthOfLongestSubstring(first);
    printf("%d\n", one);

    // char second[] = "au";
    // int two = lengthOfLongestSubstring(second);
    // printf("%d\n", two);

    // char third[] = "pwwkew";
    // int three = lengthOfLongestSubstring(third);
    // printf("%d\n", three);

    // printf("1: %d\n2: %d\n3: %d\n", one, two, three);
    return 0;
}
