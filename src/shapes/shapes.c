#include <stdbool.h>
#include "shapes.h"

bool pointInsideShape(Point p, Shape s) {
    
    switch(s.type) {

        case SHAPE_RECTANGLE:
            return pointInsideRectangle(p, s.rect);

        case SHAPE_CIRCLE:
            return pointInsideCircle(p, s.circ);

    }
    return false;
}
