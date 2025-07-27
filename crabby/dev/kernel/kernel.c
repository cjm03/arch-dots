/*
*  kernel.c
*/
void kmain(void)
{
    const char* str = "my first kernel";
    char* vidptr = (char*)0xb8000; // video memory begins here
    unsigned int i = 0;
    unsigned int j = 0;

    // This loop clears the screen.
    // 25 lines of 80 columns each; each element takes 2 bytes
    while (j < 80 * 25 * 2) {
        vidptr[j] = ' ';
        vidptr[j + 1] = 0x07;
        j = j + 2;
    }

    j = 0;

    while (str[j] != '\0') {
        vidptr[i] = str[j];
        vidptr[i + 1] = 0x07;
        ++j;
        i = i + 2;
    }
    return;
}
