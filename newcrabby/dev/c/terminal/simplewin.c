#include <X11/Xlib.h>
#include <X11/Xutil.h>

int main(int argc, char* argv[]) {
    Display                 *mydisplay;
    XSetWindowAttributes    myat;
    Window                  mywindow;
    XEvent                  myevent;
    int                     screen_num, done;
    unsigned long           valuemask;

    mydisplay = XOpenDisplay("");

    screen_num = DefaultScreen(mydisplay);
    myat.background_pixel = WhitePixel(mydisplay, screen_num);
    valuemask = CWBackPixel;
    mywindow = XCreateWindow(mydisplay, RootWindow(mydisplay, screen_num),
                             200, 200, 350, 250, 2,
                             DefaultDepth(mydisplay, screen_num), InputOutput,
                             DefaultVisual(mydisplay, screen_num),
                             valuemask, &myat);

    XMapWindow(mydisplay, mywindow);

    XNextEvent(mydisplay, &myevent);
}
