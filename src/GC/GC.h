#ifndef __GC_H
#define __GC_H 1    

#include <X11/X.h>
#include <err.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/Xatom.h>
#include <X11/Xft/Xft.h>

#include "../def.h"

typedef enum {
    LINE_STYLE = LineSolid,
    LINE_WIDTH = 5,
    CAP_STYLE  = CapRound,
    JOIN_STYLE = JoinMiter,
    FILL_STYLE = FillSolid,
} defaultGCProperties;

GC createGraphicContent(
    unsigned int lineWidth, 
    Window win,
    unsigned long fgColor, 
    unsigned long bgColor
);

/*
    @brief Takes input of lineWidth from the user
*/
GC takeGraphicContentInput(Window win);

/*
    @brief: Creates a default graphic content
    with predefined attributes.
*/
GC openDefaultGraphicContent(Window win);

#endif /* __GC_H */