#pragma once
#include <vector>
#include "../CNC/instruction.h"

class Shape{
    public:
        Shape(){

        }
        Shape(const Shape& shape){

        }
        Shape(Shape&& shape){

        }
        virtual std::vector<Instruction> getInstructions()=0;
        virtual ~Shape(){

        }
};