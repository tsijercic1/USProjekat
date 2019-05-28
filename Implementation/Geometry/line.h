#pragma once
#include "shape.h"
#include "point.h"

class Line:public Shape{
        Point start,end;
    public:
        Line(Point start, Point end):start(start),end(end){
            
        }
        std::vector<Instruction> getInstructions(){
            
        }
};