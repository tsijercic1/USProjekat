#pragma once

class Point {
public:
    double x, y;
    
<<<<<<< HEAD
    Point() {
        x = 0;
        y = 0;
    }
    
=======
    Point(){
        x=0;
        y=0;
    }

>>>>>>> 34a2f75c1f91673e5ca0a1a70b5422c7396b9a14
    Point(double x, double y) {
        Point::x = x;
        Point::y = y;
    }
<<<<<<< HEAD
};
=======
    
    Point(const Point& point){
        x=point.x;
        y=point.y;
    }
};
>>>>>>> 34a2f75c1f91673e5ca0a1a70b5422c7396b9a14
