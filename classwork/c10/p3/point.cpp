#include "point.h"
#include <math.h>
#include <stdlib.h>

Point::Point() : x(0), y(0) {
}

void Point::move(double dx, double dy) {
    x += dx;
    y += dy;
}

double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}

double Point::distanceFrom(Point const& p) {
    double x1 = p.getX();
    double y1 = p.getY();
    return sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
}
