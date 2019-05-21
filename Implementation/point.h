#pragma once

class Point {
public:
    double x, y;
    
    Point() {
        x = 0;
        y = 0;
    }
    
    Point(double x, double y) {
        Point::x = x;
        Point::y = y;
    }
};
