#pragma once
#include "point.h"
class Circle {
    private:
        Point center;
        const double radius;

    public:
        Circle(Point p, double r);
        Circle();
        Point getCenter() const;
        double getRadius() const;
        void move(double dx, double dy);
        double intersectionArea(const Circle & otherCircle);

};

