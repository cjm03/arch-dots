#include <X11/Xlib.h>
#include <X11/Xutil.h>

int main(int argc, char* argv[])
{
    Display *mydisplay;
    mydisplay = XOpenDisplay("");
    XBell(mydisplay, 0);
    XCloseDisplay(mydisplay);
}
