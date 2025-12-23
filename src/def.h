#ifndef _DEF_H
#define _DEF_H 1

/*
    Inclusions
*/

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/Xatom.h>
#include <X11/Xft/Xft.h>

/*
    Global display attributes
*/

Display* disp;
int screenNum;
Window rootWindow;
Visual* mainVisual;

// Construction of necessary resources
void constructDisplay();

/*
    @brief: Frees the resources
*/
void destroyDisplay(
    Window* win, 
    GC* gc
    // Visual* vis
);

#endif // End of __DEF_H guard