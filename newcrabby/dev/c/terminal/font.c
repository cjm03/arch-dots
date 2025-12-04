#include <X11/X.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>

struct {
    int width;
    int height;
    char* text;
    int textlen;

    /* X Windows related vars */

    Display* display;
    int screen;
    Window root;
    Window window;
    GC gc;
    XFontStruct* font;
    unsigned long blackpixel;
    unsigned long whitepixel;
} textbox;

static void x_connect(void) {
    textbox.display = XOpenDisplay(NULL);
    if (!textbox.display) {
        fprintf(stderr, "Couldnt open display.\n");
        exit(1);
    }
    textbox.screen = DefaultScreen(textbox.display);
    textbox.root = RootWindow(textbox.display, textbox.screen);
    textbox.blackpixel = BlackPixel(textbox.display, textbox.screen);
    textbox.whitepixel = WhitePixel(textbox.display, textbox.screen);
}

static void create(void)
{
    textbox.width = 300;
    textbox.height = 300;
    textbox.width = XCreateSimpleWindow(textbox.display,
                                        textbox.root,
                                        1,
                                        1,
                                        textbox.width,
                                        textbox.height,
                                        0,
                                        textbox.blackpixel,
                                        textbox.whitepixel);
    XSelectInput(textbox.display, textbox.window, ExposureMask);
    XMapWindow(textbox.display, textbox.window);
}

static void setupgc(void)
{
    textbox.screen = DefaultScreen(textbox.display);
    textbox.gc = XCreateGC(textbox.display, textbox.window, 0, 0);
    XSetBackground(textbox.display, textbox.gc, textbox.whitepixel);
    XSetForeground(textbox.display, textbox.gc, textbox.blackpixel);
}

static void setupfont(void)
{
    const char* fontname = 
}











