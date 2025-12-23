
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/Xatom.h>
#include <X11/Xft/Xft.h>

#include "def.h"
#include "color.h"
#include "window.h"
#include "GC.h"

// Global extern variable defintions
Display* disp;
int screenNum;
Window rootWindow;
Visual* mainVisual;

/*
    @brief Sets the necessary globat attributes with
    proper value.
*/

void constructDisplay() {

    if(!(disp = XOpenDisplay(NULL))) {
        errx(1, "Can't open display!\n");
        exit(1);
    }
    screenNum = DefaultScreen(disp);
    mainVisual = DefaultVisual(disp, screenNum);
    rootWindow = RootWindow(disp, screenNum);
    constructColorResources();
    return;
}

/*
    @brief: Frees the resources
*/
void destroyDisplay(Window* win, GC* gc) {
    XUnmapWindow(disp, *win);
    XDestroyWindow(disp, *win);
    XFreeGC(disp, *gc);
    destroyColorResources();
    
    //Close connection with X11
    XCloseDisplay(disp);
}