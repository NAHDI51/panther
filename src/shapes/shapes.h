#ifndef __SHAPES_H
#define __SHAPES_H

/*
    This is probably an overkill for this project, but 
    it will prove to be very useful for the window manager.
*/

#include <stdbool.h>

#include "point.h"
#include "rectangle.h"
#include "circle.h"

/*
    Adds a generic wrapper around the common properties of geometry
*/

typedef enum {
    SHAPE_RECTANGLE,
    SHAPE_CIRCLE
    /* More for later */
} ShapeType;

typedef struct {
    ShapeType type;

    union  {
        Rectangle rect; 
        Circle circ;

    };
} Shape;

/*
    @brief: Checks if a point p lies inside the shape
*/
bool pointInsideShape(Point p, Shape s);

#endif // __SHAPES_H