// X11 libraries
#include <X11/Xlib.h>
#include <stdbool.h>

#include "../def.h"
#include "../window.h"
#include "../GC/GC.h"
#include "../GC/GC_snapshot.h"

#include "point.h"
#include "rectangle.h"
#include "circle.h"

/*
    Is pass by value memory all that worth saving?
    I hope not, because they are not that heavy.
*/
int circleCenterX(Circle c) {
    return c.bounds.p.posX + c.bounds.width / 2;
}

int circleCenterY(Circle c) {
    return c.bounds.p.posY + c.bounds.height / 2;
}

/*
    If w != h, it makes ellipse, so will not work.
    Should I make it generalized for ellipse? Maybe later.
*/
int circleRadius(Circle c) {
    return c.bounds.width / 2;
}

Circle createCircle(
    Point p, 
    int width, int height, int lineWidth
) {
    return (Circle) {
        .bounds.p = p,
        .bounds.width = width, 
        .bounds.height = height,
        .bounds.lineWidth = lineWidth
    };
}

void drawCircle(
    Drawable draw, GC graphicContent,
    Circle circ, bool stroke
) {
    if(stroke) {
        // Same way we handle the rectangle.
        GCSnapshot snapLineWidth = gcSetLineWidth(graphicContent, circ.bounds.lineWidth);

        int half = circ.bounds.lineWidth/2;
        XDrawArc(
            disp, draw, graphicContent,
            circ.bounds.p.posX - half, 
            circ.bounds.p.posY - half,
            circ.bounds.width + circ.bounds.lineWidth,
            circ.bounds.height + circ.bounds.lineWidth,
            0, 360*64
        );
        gcRestore(graphicContent, snapLineWidth);
    } else {
        XFillArc(
            disp, draw, graphicContent, 
            circ.bounds.p.posX, circ.bounds.p.posY,
            circ.bounds.width, circ.bounds.height,
            0, 360*64
        );
    }
}

bool pointInsideCircle(Point p, Circle c) {
    int cx = circleCenterX(c);
    int cy = circleCenterY(c);
    int r = circleRadius(c);

    return pointDistSq((Point) {cx,cy}, p) <= r*r;
}