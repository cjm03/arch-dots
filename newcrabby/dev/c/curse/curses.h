#ifndef CURSES_H
#define CURSES_H

// #define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <asm/termbits.h>

#define stringcopy(dst, src, size)  strncpy((dst), (src), (size))
#define copy(dst, src, size)        memcpy($c (dst), $c (src), (size))
#define stringlen(x)                strlen($c (x))

#define cprint(f,args...) do { \
    int8 _buf[256]; \
    \
    zero($1 &_buf, 256); \
    snprintf($c _buf, 255, $c (f), args); \
    cprint_(globalstate->current, _buf); \
} while (false)
#define update()            cupdate(globalstate->current)
#define cgetxy(w)           (win)
#define getxy()             (globalstate->current)

#define packed __attribute((packed))
#define public __attribute((visibility("default")))
#define protected __attribute((visibility("hidden")))
#define _init __attribute((constructor))
#define _fini __attribute((destructor))
#define private static

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;
typedef unsigned short int frame;


#define $1 (int8 *)
#define $2 (int16)
#define $4 (int32)
#define $8 (int64)
#define $c (char*)
#define $i (int)



#define getbit(bm, bit)  ((bm[((bit) / 8)] & (1 << ((bit) % 8))))
        // >> ((bit) % 8))
#define setbit(bm, bit)  bm[((bit) / 8)] |= (1 << ((bit) % 8))
#define unsetbit(bm, bit)  bm[((bit) / 8)] &= ~(1 << ((bit) % 8))

enum {
    Undefined, Char, Special
} packed;

enum E_SKey {
    None, LeftArrow, UpArrow, RightArrow, DownArrow
} packed;
typedef enum E_SKey skey;

struct S_Framebuffer {
    frame* frames;
    int16 f1b;
    int8 bitmap[];
} packed;
typedef struct S_Framebuffer framebuffer;

struct S_Window {
    int8 id;
    int8 x;
    int8 y;
    int8 cols;      // width
    int8 rows;      // height
    int8 title[16];
    bool active;
    framebuffer* fb;
} packed;
typedef struct S_Window window;

struct S_State {
    int8 nextid;
    window* root;
    window* current;
    struct termios term;
} packed;
typedef struct S_State state;

struct S_Key {
    int8 tag:2;
    union {
        skey code;
        int8 ch;
    } packed;
} packed;
typedef struct S_Key key;


// CONSTRUCTORS
private framebuffer* mkfb(int16 num);
public window* mkwin(state* st, int8 cols, int8 rows, int8* title);
private state* mkstate(void);

public _init void initlibrary(void);
public _fini void exitlibrary(void);

private void sfblinear(window* win, int8 c, int8 fgcolor, int8 bgcolor, int16 idx);
private void sfbxy(window* win, int8 c, int8 fgcolor, int8 bgcolor, int8 x, int8 y);
private void updatewin(window* win, int8 c, int8 fgcolor, int8 bgcolor);
private key* cgetchar(void);
private int8 creadchar(void);
private void termenable(state* st);
private void termdisable(state* st);

public void cputchar(window*, int8, int8, int8);
public void cjump(window* win, int8 x, int8 y);
public void cupdate(window* win);
public void cframeset(window* win, int8 c, int8 fg, int8 bg);
public void cprint_(window* win, int8* str);

protected void ansimove(int8 x, int8 y);
protected int8* ansicolor(int8 fg, int8 bg);
protected int8* ansireset(void);
protected void ansimode(void);

private void showkey(key* k);

protected void showfb(framebuffer* fb, int16 num);
protected void showwin(window* window);
protected void showstate(state* state);

#endif // CURSES_H
