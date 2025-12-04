// ansi.c
#include "curses.h"
#include "util.h"


// ESC[{line};{column}H


protected void ansimove(int8 x, int8 y) {
    int8 buf[16];
    int8 n;

    zero($1 &buf, 16);
    snprintf($c buf, 15, "\x1b[%d;%dH", (char)y, (char)x);
    n = stringlen(buf);
    write(1, buf, n);
}

// Set style to dimmed white fg w/ red bg: \x1b[2;37;41m
protected int8* ansicolor(int8 fg, int8 bg) {
    static int8 buf[16];
    int8* bufptr;
    int8 fgcolor, bgcolor;

    fgcolor = fg + 30;
    bgcolor = bg + 40;
    zero($1 &buf, 16);
    snprintf($c buf, 15, "\x1b[0;%d;%dm", (char)fgcolor, (char)bgcolor);
    bufptr = $1 &buf;

    return bufptr;
}
protected int8* ansireset(void) {
    return $1 "\x1b[0m";
}

protected void ansimode(void) {
    write(1, "\x1b[=1h", 5);
    write(1, "\x1b[2J", 4);
    return;
}
