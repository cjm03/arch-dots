#include <X11/Xlib.h>
#include <stdio.h>

int main(void) {
    Display *e6display;
    Screen  *screenptr;
    int     screen_num;

    e6display = XOpenDisplay("");
    screen_num = DefaultScreen(e6display);
    screenptr = ScreenOfDisplay(e6display, screen_num);

    printf("Macro = %d\n", DoesSaveUnders(screenptr));
    if (DoesSaveUnders(screenptr)) {
        printf("Does screen unders\n");
    } else {
        printf("Does NOT provide screen unders\n");
    }
    switch (DoesBackingStore(screenptr)) {
        case WhenMapped:
            printf("Backing store provided when window is mapped\n");
            break;
        case Always:
            printf("Backing store always provided\n");
            break;
        case NotUseful:
            printf("Does NOT provide backing store\n");
            break;
        default:
            printf("Something wrong with DoesBackingStore() call\n");
    }
    XCloseDisplay(e6display);
}
