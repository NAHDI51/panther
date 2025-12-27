#include "point.h"

Point createPoint(int x, int y) {
    return (Point) {x, y};
}

Point pointAdd(Point a, Point b) {
    return (Point) {
        .posX = a.posX + b.posX,
        .posY = a.posY + b.posY
    };
}

Point pointSubtract(Point a, Point b) {
    return (Point) {
        .posX = a.posX - b.posX,
        .posY = a.posY - b.posY
    };
}

int dotProduct(Point a, Point b) {
    return a.posX * b.posX + 
           a.posY * b.posY;
}

int pointDistSq(Point a, Point b) {
    Point dPoint = pointSubtract(a, b);

    return 
    dPoint.posX * dPoint.posX +
    dPoint.posY * dPoint.posY;
}