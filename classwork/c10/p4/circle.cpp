#include "circle.h"
#include <math.h>
#include <stdio.h>

Circle::Circle(Point p, double r) : center(p), radius(r) {
}

Circle::Circle(): center(Point()), radius(0) {
}

Point Circle::getCenter() const {
    return center;
}

double Circle::getRadius() const {
    return radius;
}

void Circle::move(double dx, double dy) {
    center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
    double d = center.distanceFrom(otherCircle.getCenter());
    //fprintf(stderr, "d=%f\n", d);
    double r = radius;
    //fprintf(stderr, "r=%f\n", r);
    double R = otherCircle.getRadius();
    //fprintf(stderr, "R=%f\n", R);
    // error handle: if a circle has no radius
    if (r==0 || R==0 || r+R<=d) {
        return 0;
    }

    if (d==0){
        r = r<R ? r:R;
        return M_PI*r*r;
    }
    if ( ((((d+r <= r)||(-d-R >= -r)) && (r>R))) || \
        ((((d+r <= R)||(-d-r >= -R)) && (r<R)))){
        //if overlap completely, do pi*r^2 with the smaller radius
        r = r<R ? r:R;
        return M_PI*r*r;
    }
    double part1 = r*r*acos( (d*d+r*r-R*R)/(2*d*r));
    //fprintf(stderr, "part1=%f\n", part1);
    double part2 = R*R*acos( (d*d+R*R-r*r)/(2*d*R));
    //fprintf(stderr, "part2=%f\n", part2);
    double part3 = 0.5*sqrt( (-d+r+R)*(d+r-R)*(d-r+R)*(d+r+R));
    //fprintf(stderr, "part3=%f\n", part3);
    return part1+part2-part3;
}





