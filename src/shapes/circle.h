#ifndef __CIRCLE_H
#define __CIRCLE_H

// X11 libraries
#include <X11/Xft/Xft.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/X.h>

#include "rectangle.h"
#include "../def.h"
#include "../window.h"
#include "../color.h"
// #include "../colorbox.h"

/*
    NOTE THAT these are pure geometric objects,
    and doesn't have colors.
*/


/*
    In X11, circle appears as an "Area within rectangle",
    so it is worth noting that I can take the attributes of 
    a rectangle, and add center, radius effectively to make a 
    circle. 

    Why should I incorporate rectangle?

    Because X11 XdrawArc and similar functions actually use 
    posX, posY, width height in order to draw a circle. 

    How can I acquire centerX, centerY, etc? 
    Conics formulas: (width + x, height + y), and you'll get 
    a circle.
*/
typedef struct {
    Rectangle bounds;
} Circle;

// Use these methods to get them, not store them in data.
int circleCenterX(Circle c);
int circleCenterY(Circle c);
int circleRadius(Circle c);

Circle createCircle(
    Point p,
    int width, int height,
    int lineWidth
);

void drawCircle(
    Drawable draw,
    GC graphicContent,
    Circle circ,
    bool stroke
);

bool pointInsideCircle (
    Point p,
    Circle c
);


#endif  // __CIRCLE_H