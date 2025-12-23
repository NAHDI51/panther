#ifndef _MAIN_H
#define _MAIN_H 1

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

static Display* disp;
static int screenNum;
static Window rootWindow;
static Visual* mainVisual;

#endif // End of _MAIN_H guard