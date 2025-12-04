#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int screennum, width, height;
    unsigned long bg, border;
    Window w;
    XEvent ev;
    Display* d;

    d = XOpenDisplay(NULL);
    if (!d) {
        fprintf(stderr, "unable to open display\n");
        return 7;
    }

    screennum = DefaultScreen(d);
    bg = BlackPixel(d, screennum);
    border = WhitePixel(d, screennum);

    width = 40;
    height = 40;

    w = XCreateSimpleWindow(d, DefaultRootWindow(d),
                            0, 0,
                            width, height,
                            2, border,
                            bg);
    XSelectInput(d, w, ButtonPressMask | StructureNotifyMask);
    XMapWindow(d, w);

    while (1) {
        XNextEvent(d, &ev);
        switch (ev.type) {
            case ConfigureNotify:
                if (width !=  ev.xconfigure.width || height != ev.xconfigure.height) {
                    width = ev.xconfigure.width;
                    height = ev.xconfigure.height;
                    printf("Dimensions changed to %d by %d\n", width, height);
                }
                break;
            case ButtonPress:
                XCloseDisplay(d);
                break;
        }
    }
    return 0;
}
