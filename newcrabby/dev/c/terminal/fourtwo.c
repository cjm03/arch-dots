#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>

#define BACKINGWIDTH 16
#define BACKINGHEIGHT 16
static unsigned char backingbits[] = {
    0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
    0xff, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
    0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff
};

int main(int argc, char* argv[]) {
    Display                 *mydisplay;
    XSetWindowAttributes    myat;
    Window                  mywindow, win1, win2, ontop;
    XWindowChanges          alter;
    XSizeHints              wmsize;
    XWMHints                wmhints;
    XTextProperty           windowName, iconName;
    XEvent                  myevent;
    GC                      gc;
    char* window_name =     "Uncover";
    char* icon_name   =     "Uc";
    int                     screen_num, done;
    unsigned long           valuemask;
    Pixmap                  back;
    int                     count;

    mydisplay = XOpenDisplay("");

    screen_num = DefaultScreen(mydisplay);
    myat.background_pixel = WhitePixel(mydisplay, screen_num);
    myat.border_pixel = BlackPixel(mydisplay, screen_num);
    myat.event_mask = ExposureMask;
    myat.save_under = True;
    valuemask = CWBackPixel | CWBorderPixel | CWEventMask | CWSaveUnder;
    mywindow = XCreateWindow(mydisplay, RootWindow(mydisplay, screen_num),
                             200, 200, 350, 250, 2,
                             DefaultDepth(mydisplay, screen_num), InputOutput,
                             DefaultVisual(mydisplay, screen_num),
                             valuemask, &myat);
    back = XCreatePixmapFromBitmapData(mydisplay, mywindow,
                                       backingbits, BACKINGWIDTH, BACKINGHEIGHT,
                                       BlackPixel(mydisplay, screen_num),
                                       WhitePixel(mydisplay, screen_num),
                                       DefaultDepth(mydisplay, screen_num));
    XSetWindowBackgroundPixmap(mydisplay, mywindow, back);

    wmsize.flags = USPosition | USSize;
    XSetWMNormalHints(mydisplay, mywindow, &wmsize);
    wmhints.initial_state = NormalState;
    wmhints.flags = StateHint;
    XSetWMHints(mydisplay, mywindow, &wmhints);
    XStringListToTextProperty(&window_name, 1, &windowName);
    XSetWMName(mydisplay, mywindow, &windowName);
    XStringListToTextProperty(&icon_name, 1, &iconName);
    XSetWMIconName(mydisplay, mywindow, &iconName);

    gc = XCreateGC(mydisplay, mywindow, 0, NULL);
    XSetForeground(mydisplay, gc, BlackPixel(mydisplay, screen_num));
    XSetBackground(mydisplay, gc, WhitePixel(mydisplay, screen_num));

    win1 = XCreateWindow(mydisplay, mywindow, 100, 30, 50, 70, 2,
                         DefaultDepth(mydisplay, screen_num), InputOutput,
                         DefaultVisual(mydisplay, screen_num),
                         valuemask, &myat);
    win2 = XCreateWindow(mydisplay, mywindow, 100, 150, 150, 30, 2,
                          DefaultDepth(mydisplay, screen_num), InputOutput,
                          DefaultVisual(mydisplay, screen_num),
                          valuemask, &myat);
    myat.background_pixel = BlackPixel(mydisplay, screen_num);
    ontop = XCreateWindow(mydisplay, mywindow, 120, 40, 80, 130, 2,
                          DefaultDepth(mydisplay, screen_num), InputOutput,
                          DefaultVisual(mydisplay, screen_num),
                          valuemask, &myat);

    XMapWindow(mydisplay, mywindow);
    XMapWindow(mydisplay, win1);
    XMapWindow(mydisplay, win2);

    done = 0;
    count = 0;
    while (done == 0) {
        XFlush(mydisplay);
        XNextEvent(mydisplay, &myevent);
        sleep(2);
        switch (myevent.type) {
            case Expose:
                count++;
                switch (count) {
                    case 1:
                        XFillRectangle(mydisplay, win1, gc, 0, 0, 50, 70);
                        XFillRectangle(mydisplay, win2, gc, 0, 0, 150, 30);
                        break;
                    case 3:
                        XMapWindow(mydisplay, ontop);
                        break;
                    case 6:
                        XUnmapWindow(mydisplay, ontop);
                        break;
                    case 9:
                        XUnmapWindow(mydisplay, win2);
                        break;
                    default:
                        break;
                }
                break;
        }
    }

    XUnmapWindow(mydisplay, mywindow);
    XDestroyWindow(mydisplay, mywindow);
    XCloseDisplay(mydisplay);
}
