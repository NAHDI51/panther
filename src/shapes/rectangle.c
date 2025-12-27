#include <X11/Xlib.h>

#include "../def.h"
// #include "../window.h"
#include "../color.h"
#include "../GC/GC.h"
#include "../GC/GC_snapshot.h"

#include "point.h"
#include "rectangle.h"

/*
    NOTE THAT these are pure geometric objects,
    and doesn't have colors.
*/

Rectangle createRectangle(
    Point p, 
    int width, int height, int lineWidth) 
{
    return (Rectangle) {
        .p = p,
        .height = height,
        .width = width,
        .lineWidth = lineWidth
    };
}

void drawRectangle(
    Drawable draw, 
    GC graphicContent,
    Rectangle rect,
    bool stroke
) {
    if(stroke) {
        /*
            This case is a bit complicated.

            We need to store the past GC state, setLineAttribute, 
            Draw the stroke, then reset the current GC state. This 
            is done because line Width is integral to the attributes
            of GC.
        */
        GCSnapshot snap = gcSetLineWidth(graphicContent, rect.lineWidth);
        
        int half = rect.lineWidth/2;
        XDrawRectangle(
            disp, draw, graphicContent,
            rect.p.posX - half, rect.p.posY - half,
            rect.width + rect.lineWidth, rect.height + rect.lineWidth
        );

        gcRestore(graphicContent, snap);
    } else {
        // Otherwise, we don't change any inner settings, and simply draw
        XFillRectangle(
            disp, draw, graphicContent,
            rect.p.posX, rect.p.posY,
            rect.width, rect.height
        );
    }
}

bool pointInsideRectangle(Point p, Rectangle r) {
    return p.posX >= r.p.posX &&
           p.posX < r.p.posX + r.width &&
           p.posY >= r.p.posY &&
           p.posY < r.p.posY + r.height;
}

