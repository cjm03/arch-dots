// curses.c
// MAN 2 IOCTL_TTY
  
#include "curses.h"
#include "util.h"
#include "ansi.h"
#include <asm-generic/termbits.h>

public state* globalstate;

private void showkey(key* k) {
    if (!k)
        return;

    switch (k->tag) {
        case Char:
            cprint("%c ", (char)k->ch);
            break;
        
        case Special:
            switch(k->code) {
                case UpArrow:
                    cprint("%s ", "Up");
                    break;
                case DownArrow:
                    cprint("%s ", "Down");
                    break;
                case LeftArrow:
                    cprint("%s ", "Left");
                    break;
                case RightArrow:
                    cprint("%s ", "Right");
                    break;
                case None:
                    cprint("%s ", "None");
                    break;
                default:
                    cprint("%s ", "(other)");
                    break;
            }
            break;
        
        default:
            cprint("%s ", "error");
            break;
    }
    update();

    return;
}

public void cprint_(window* win, int8* str) {
    int8* p;

    if (!win) return;

    p = str;
    while (*p) {
        cputchar(win, *p++, Black, White);
    }
}

public void cframeset(window* win, int8 c, int8 fg, int8 bg) {
    int16 idx, max;

    if (!win) return;

    max = ((win->cols - 1) * (win->rows - 1));
    for (idx = 0; idx < max; idx++) {
        sfblinear(win, c, fg, bg, idx);
    }
    return;
}

protected void showfb(framebuffer* fb, int16 num) {
    int8 color;
    int8 fg, bg;
    int8 c;
    frame frm; 
    int16 idx;
    bool bit;

    printf("Frames:\n  ");
    for (idx = 0; idx < num; idx++) {
        frm = fb->frames[idx];
        if (!frm) {
            printf("00");
        } else {
            c = ((frm & 0xff00) >> 8);
            color = (frm & 0x00ff);
            bg = ((color & 0x00f0) >> 4);
            fg = (color & 0x000f);
            if (!c) printf("0/");
            else printf("%c/", (char)c);
            printf("%d/%d", $i bg, $i fg);
        }
        printf(" ");
        if (!(idx % 8)) printf("\n  ");
    }
    printf("\n1st one-byte:\n 0x%.04hx\n", fb->f1b);
    printf("Bitmap:\n");
    for (idx = 0; idx < num; idx++) {
        bit = getbit(fb->bitmap, idx);
        printf("%d", (bit) ? 1 : 0);
        if (!(idx % 64)) printf("\n  ");
        else if (!(idx % 8)) printf(" ");
    }
    printf("\n\n");
    printf("(%d)\n", (getbit(fb->bitmap, 0x018b-3)) ? 1 : 0);
    return;
    
}

public void cupdate(window* win) {
    bool bit;
    int16 idx;
    int16 max;
    frame fr;
    int16 color;
    int8 fg, bg;
    int8 c;
    int8 byte;
    int8 x, y;

    if (!win) return;
    else if (!win->active) return;

    max = ((win->cols - 1) * (win->rows - 1));
    for (idx = (win->fb->f1b - 1); idx <= max; idx++) {
        byte = win->fb->bitmap[(idx / 8)];
        if (!byte) continue;

        bit = getbit(win->fb->bitmap, idx);
        if (!bit) continue;
        fr = win->fb->frames[idx];

        c = ((fr & 0xff00) >> 8);
        color = (fr & 0x00ff);
        bg = ((color & 0x00f0) >> 4);
        fg = (color & 0x000f);

        y = (idx / (win->rows - 1));
        x = (idx % (win->rows - 1));
        win->y = y;
        win->x = x;

        updatewin(win, c, fg, bg);
        unsetbit(win->fb->bitmap, idx);
        win->fb->frames[idx] = 0;

    }

    win->fb->f1b = 0;
}

private void updatewin(window* win, int8 c, int8 fgcolor, int8 bgcolor) {
    int8 *ansi, *reset;
    int8 buf[32];
    int16 n;

    if (!win) return;

    ansimove(win->x, win->y);
    ansi = ansicolor(fgcolor, bgcolor);
    reset = ansireset();
    zero($1 &buf, 32);
    snprintf($c buf, 31, "%s%c%s", $c ansi, (char)c, $c reset);
    n = stringlen(buf);
    write(1, $c buf, $i n);

    return;
}

private void termdisable(state* st) {
    if (!st) return;

    ioctl(0, TCSETS, &st->term);      // ret will be 0 on success
    return;
}

private void termenable(state* st) {
    struct termios term;
    signed int ret;

    if (!st) return;

    ret = ioctl(0, TCGETS, &term);      // ret will be 0 on success
    if (ret) return;

    copy(&st->term, &term, sizeof(struct termios));
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    term.c_lflag &= ~(ECHO | ICANON);

    ioctl(0, TCSETS, &term);
    return;
}

private int8 creadchar(void) {
    signed int n;
    int8 buf[2];

    zero($1 &buf, 4);
    n = read(0, $c buf, 1);
    if (n > 0) return (int8)*buf;
    else return 0;
}

private key* cgetchar(void) {
    int16 n;
    int8 byte;
    key* p;

    byte = creadchar();
    if (!byte) return (key*)0;

    n = sizeof(struct S_Key);
    p = (key*)malloc($i n);
    if (!p) return (key*)0;
    zero($1 p, n);
    p->tag = Undefined;

    switch (byte) {
        case '\x1b':
            p->tag = Special;
            byte = creadchar();
            if (byte == 0x5b) {
                byte = creadchar();
                switch (byte) {
                    case 0x44:
                        p->code = LeftArrow;
                        break;

                    case 0x41:
                        p->code = UpArrow;
                        break;

                    case 0x43:
                        p->code = RightArrow;
                        break;

                    case 0x42:
                        p->code = DownArrow;
                        break;

                    default:
                        p->code = None;
                }
            } else {
                p->code = None;
            }
            return p;
            break;

        default:
            p->tag = Char;
            p->ch = byte;

            break;
    }
    return p;
}

public void cputchar(window* win, int8 c, int8 fg, int8 bg) {
    int8 maxx, maxy;
    int8 x, y;

    if (!win) return;

    x = win->x;
    y = win->y;
    maxx = (win->cols - 1);
    maxy = (win->rows - 1);

    if (x < maxx) {
        win->x++;
    } else if (y == maxy) {
        win->x = win->y = 0;
    } else {
        win->x = 0;
        win->y++;
    }
    return sfbxy(win, c, fg, bg, x, y);
}

public void cjump(window* win, int8 x, int8 y) {
    int8 maxx, maxy;

    if (!win) return;

    maxx = (win->cols - 1);
    maxy = (win->rows - 1);

    if ((x > maxx) || (y > maxy)) return;

    win->x = x;
    win->y = y;

    return;
}

private void sfblinear(window* win, int8 c, int8 fgcolor, int8 bgcolor, int16 idx) {

    int8 color;
    frame fr;
    int16 maxidx;

    if (!win || !win->fb || !win->fb->frames) return;

    maxidx = ((win->cols - 1) * (win->rows - 1));
    if (idx > maxidx) return;

    color = (bgcolor << 4) | fgcolor;
    fr = (c << 8) | color;

    if (win->fb->frames[idx] != fr) {
        win->fb->frames[idx] = fr;
        if (!win->fb->f1b || (win->fb->f1b > idx)) {
            win->fb->f1b = idx;
        }
        setbit(win->fb->bitmap, idx);
    }

    return;
}

private void sfbxy(window* win, int8 c, int8 fgcolor, int8 bgcolor, int8 x, int8 y) {

    int16 idx;
    int8 maxx, maxy;

    if (!win) return;

    maxx = (win->cols - 1);
    maxy = (win->rows - 1);

    if ((x > maxx) || (y > maxy)) return;

    idx = ((y * maxy) + x);

    return sfblinear(win, c, fgcolor, bgcolor, idx);
}

private framebuffer* mkfb(int16 num) {
    int8 parity;
    int16 fmsize, fbsize, bmsize;
    framebuffer* fb;
    frame* fm;

    assert(num > 0);

    fmsize = (sizeof(frame) * num);
    fm = (frame*)malloc($i fmsize);
    assert(fm);
    zero($1 fm, fmsize);

    parity = (num % 8) ? 1 : 0;
    bmsize = ((num / 8) + parity);

    fbsize = (sizeof(struct S_Framebuffer) + bmsize);
    fb = (framebuffer*)malloc($i fbsize);
    assert(fb);
    zero($1 fb, fbsize);

    fb->frames = fm;
    fb->f1b = 0;

    return fb;
}

private state* mkstate(void) {
    state* st;
    int16 size;

    size = sizeof(struct S_State);
    st = (state*)malloc($i size);
    assert(st);

    zero($1 st, size);
    st->nextid = 0;

    return st;
}

public window* mkwin(state* st, int8 cols, int8 rows, int8* title) {
    window* win;
    int16 size;
    int16 n;

    assert(cols && rows && title);
    size = sizeof(struct S_Window);
    win = (window*)malloc($i size);
    assert(win);
    zero($1 win, size);

    win->id = st->nextid++;
    win->x = win->y = 0;        // TOP LEFT CORNER OF SCREEN
    win->cols = cols;
    win->rows = rows;
    stringcopy($c win->title, $c title, 15);
    if (!win->id) {
        win->active = true;
        st->root = win;
        st->current = win;
    } else {
        win->active = false;
    }
    n = (cols * rows);
    win->fb = mkfb(n);
    if (!win->fb) {
        free(win);
        return (window*)0;
    }
    return win;
}

public _init void initlibrary(void) {
    globalstate = mkstate();
    termenable(globalstate);
    (volatile void)mkwin(globalstate, 15, 15, $1 "Root Window");

    return;
}

public _fini void exitlibrary(void) {
    if (globalstate) termdisable(globalstate);
    return;
}

int main(void)
{
    key* k;
    window* win;
    int8 x, y;
    bool cont;
    win = globalstate->current;

    cont = true;
    ansimode();
    cframeset(win, ' ', Black, White);
    cjump(win, 7, 7);
    x = getxy()
        ->x;
    y = getxy()
        ->y;

    while (cont) {
        cjump(win, x, y);
        cframeset(win, ' ', Black, White);
        cputchar(win, (int8)'o', Green, White);
        update();
        k = cgetchar();
        showkey(k);
        if (!k) continue;
        else if (k->tag == Char) {
            if (k->ch == (int8)'q') {
                cont = false;
                break;
            }
        }
        switch (k->code) {
            case UpArrow:
                if (!y) {
                    free(k);
                    continue;
                }
                cprint("%d, %d", x, y);
                y--;
                break;
            case DownArrow:
                if (y > 11) {
                    free(k);
                    continue;
                }
                cprint("%d, %d", x, y);
                y++;
                break;

            case LeftArrow:
                if (!x) {
                    free(k);
                    continue;
                }
                cprint("%d, %d", x, y);
                x--;
                break;

            case RightArrow:
                if (x > 11) {
                    free(k);
                    continue;
                }
                cprint("%d, %d", x, y);
                x++;
                break;
            default:
                continue;
        }
        free(k);
    }
    return 0;
}

// int main(int argc, char** argv)
// {
//     window* win;
//     int16 max, n;
//     int16 num;
//     key* k;
//     int8 x, y;
//
//     win = globalstate->root;
//     ansimode();
//     cframeset(win, ' ', Black, White);
//     update();
//     cjump(win, 1, 3);
//     x = getxy()
//         ->x;
//     y = getxy()
//         ->y;
//     cprint("x=%d y=%d", x, y);
//
//     num = ((win->cols - 1) * (win->rows - 1));
//
//     update();
//     cgetchar();
//
//
//     return 0;
// }
