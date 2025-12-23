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
#endif

/*
    inclusions
*/

#include <X11/Xft/Xft.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/X.h>
#include "main.h"

/*
    Visual colors
    !!! WARNING: They are not hexadecimal values, they are
    string representations of hexadecimal values !!!
*/

typedef char* ColorCode;

// Indexed from 0 to 7
#define BLACKCOLOR   (ColorCode*) "#000000"
#define WHITECOLOR   (ColorCode*) "#FFFFFF"
#define BLUECOLOR    (ColorCode*) "#0000FF"
#define GREENCOLOR   (ColorCode*) "#00FF00"
#define REDCOLOR     (ColorCode*) "#FF0000"
#define YELLOWCOLOR  (ColorCode*) "#FFFF00"
#define CYANCOLOR    (ColorCode*) "#00FFFF"
#define MAGENTACOLOR (ColorCode*) "#FF00FF"

ColorCode* colorCodes[] = {
    BLACKCOLOR,
    WHITECOLOR,
    BLUECOLOR,
    GREENCOLOR,
    REDCOLOR,
    YELLOWCOLOR,
    CYANCOLOR,
    MAGENTACOLOR
};

// They need to be initialized by createColor function before use
XftColor* colorResources[8];

/*
    @brief: Creates color based on the hex provided.
*/
static void createColor(
    XftColor* colorResource, 
    ColorCode colorCode
);
static void initializeColorResources();

