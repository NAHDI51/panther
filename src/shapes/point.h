#ifndef __POINT_H
#define __POINT_H

#include <stdbool.h>

/*
    Important for handling rectangle circle and triangle.
*/
typedef struct {
    int posX, posY;
} Point;

Point createPoint(int x, int y);
Point pointAdd(Point a, Point b);
Point pointSubtract(Point a, Point b);

int dotProduct(Point a, Point b);


// Note: it returns un-square-rooted distance
int pointDistSq(Point a, Point b);

#endif //__POINT_H