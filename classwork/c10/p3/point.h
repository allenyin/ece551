#pragma once
class Point {
    private:
        double x;
        double y;
    public:
        Point();
        void move(double dx, double dy);
        double distanceFrom(const Point & p);
        double getX() const;
        double getY() const;
};

