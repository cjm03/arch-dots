#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define RGB(r, g, b) \
        (unsigned long)((((r) & 0xFF) << 16) + (((g) & 0xFF) << 8) + ((b) & 0xFF))

int main(int argc, char* argv[]) {
    Display                 *mydisplay;             // the display to draw the window on
    XSetWindowAttributes    myat;                   // structure containing window information
    Window                  mywindow;               // the application window
    XSizeHints              sh;                     // structure containing size information
    XWMHints                wmhints;                // various window properties
    XTextProperty           windowName, iconName;   // title and icon of the window
    XEvent                  myevent;                // event information
    char* window_name =     "Test";
    char* icon_name   =     "Tico";
    int                     screen_num, done;
    unsigned long           valuemask;

    mydisplay = XOpenDisplay("");
    if (!mydisplay) {
        fprintf(stderr, "Failed to open display\n");
        return -1;
    }

    screen_num = DefaultScreen(mydisplay);
    myat.background_pixel = RGB(0x00, 0xFF, 0xFF);
    myat.border_pixel = BlackPixel(mydisplay, screen_num);
    myat.event_mask = ButtonPressMask;
    valuemask = CWBackPixel | CWBorderPixel | CWEventMask;

    mywindow = XCreateWindow(mydisplay,                             // Display
                             RootWindow(mydisplay, screen_num),     // parent window
                             200, 200,                              // x, y
                             350, 250,                              // width, height
                             2,                                     // border width
                             DefaultDepth(mydisplay, screen_num),   // Color depth of the window - color attributes (16 or 24)
                             InputOutput,                           // tells window to accept both Input and Output
                             DefaultVisual(mydisplay, screen_num),  // color information
                             valuemask,                             // specifies values to use from XSetWindowAttributes structure
                             &myat);                                // the XSetWindowAttributes structure

    sh.flags = USPosition | USSize;
    XSetWMNormalHints(mydisplay, mywindow, &sh);

    wmhints.initial_state = NormalState;
    wmhints.flags = StateHint;
    XSetWMHints(mydisplay, mywindow, &wmhints);

    XStringListToTextProperty(&window_name, 1, &windowName);
    XSetWMName(mydisplay, mywindow, &windowName);

    XStringListToTextProperty(&icon_name, 1, &iconName);
    XSetWMIconName(mydisplay, mywindow, &iconName);


    XMapWindow(mydisplay, mywindow);

    done = 0;
    while (done == 0) {
        XNextEvent(mydisplay, &myevent);
        switch (myevent.type) {
            case ButtonPress:
                printf("click\n");
                break;
            default:
                break;
        }
    }

    XUnmapWindow(mydisplay, mywindow);
    XDestroyWindow(mydisplay, mywindow);
    XCloseDisplay(mydisplay);
}
