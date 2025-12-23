/*
    * color.h
    *
    * Created on: 2011-5-19
    * 
    * color.h contains the essential definitions and macros needed 
    * across the files of the project, bundled together. It contains
    * color definitions primarily, structs and other stuffs needed 
    * for the color management of the project.
*/

#ifndef __COLOR_H
#define __COLOR_H 1

/*
    inclusions
*/

#include <X11/Xft/Xft.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/X.h>
#include "def.h"

/*
    Visual colors
    !!! WARNING: They are not hexadecimal values, they are
    string representations of hexadecimal values !!!
*/

typedef char* ColorCode;

/*
    The program will not yet support adding custom colors. 
    The 8 default colors will make up everything for the time
    being. However, I may need some other colors in the future for
    inner functionality, for which reserve colors will be used.
*/
typedef enum {
    COLOR_BLACK = 0,
    COLOR_WHITE,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_RED,
    COLOR_YELLOW,
    COLOR_CYAN,
    COLOR_MAGENTA,
    COLOR_COUNT
} ColorIndex;

static const char *colorCodes[COLOR_COUNT] = {
    [COLOR_BLACK]   = "#000000",
    [COLOR_WHITE]   = "#FFFFFF",
    [COLOR_BLUE]    = "#0000FF",
    [COLOR_GREEN]   = "#00FF00",
    [COLOR_RED]     = "#FF0000",
    [COLOR_YELLOW]  = "#FFFF00",
    [COLOR_CYAN]    = "#00FFFF",
    [COLOR_MAGENTA] = "#FF00FF"
};

// They need to be initialized by createColor function before use
XftColor* colorResources[COLOR_COUNT];

/*
    @brief: Creates color based on the hex provided.
*/
static void createColor(
    XftColor* colorResource, 
    ColorCode colorCode
);
// @brief: Initializes and destroys all the color resources
static void initializeColorResources();
static void destroyColorResources();

#endif // __COLOR_H