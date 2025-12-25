#ifndef __RECTANGLE_H
#define __RECTANGLE_H

// X11 libraries
#include <X11/Xft/Xft.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/X.h>

#include <stdbool.h>

// #include "../def.h"
// Circular dependency issue
// #include "../window.h"
#include "point.h"

typedef struct {
    // Top-left corner of the rectangle.
    Point p;
    int width, height;

    // Size of the stroke.
    int lineWidth;
} Rectangle;

/* 
    @brief: Creates rectangle from specified dimension.

    Don't take as pointers, because I'll only need the 
    values to be assigned to some other rectangle. Taking
    pointer would increase the complexity of freeing it.
*/
Rectangle createRectangle(
    Point p,
    int width,
    int height,
    int lineWidth
);

/*
    @brief: draws rectangle from the specifications. 
    if stroke is applied, lineWidth of stroke is applied.
    Drawable is either Window or a Pixmap.
*/
void drawRectangle(
    Drawable draw, 
    GC graphicContent,
    Rectangle rect,
    bool stroke
);

bool pointInsideRectangle(
    Point p,
    Rectangle r
);



#endif // __RECTANGLE_H