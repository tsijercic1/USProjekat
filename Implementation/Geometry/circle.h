//
// Created by tsijercic1 on 5/28/19.
//

#pragma once
#include "shape.h"
#include <vector>
#include <cmath>
#include "point.h"
#include "./../CNC/instruction.h"

class Circle:public Shape {
    Point center;
    double radius;
    std::vector<Instruction> instructions;
public:
    Circle(Point center, double radius);
    std::vector<Instruction> getInstructions();
    ~Circle();
};


Circle::Circle(Point center, double radius):center(center),radius(radius) {
    int numberOfSteps = 3.14159 * radius;
    double step = 2 * 3.14159 / numberOfSteps;
    {
        Instruction instruction;
        instruction.setInstructionName("moveto");
        instruction.addValue(center.x + radius);
        instruction.addValue(center.y);
        instructions.push_back(instruction);
    }
    for(int i=1;i<numberOfSteps && i*step<2*3.14159;i++){
        Instruction instruction;
        instruction.setInstructionName("lineto");
        instruction.addValue(center.x+radius*std::cos(i*step));
        instruction.addValue(center.y+radius*std::sin(i*step));
        instructions.push_back(instruction);
    }
    {
        Instruction instruction;
        instruction.setInstructionName("lineto");
        instruction.addValue(center.x + radius);
        instruction.addValue(center.y);
        instructions.push_back(instruction);
    }
    {
        Instruction instruction;
        instruction.setInstructionName("stroke");
        instructions.push_back(instruction);
    }
}

std::vector<Instruction> Circle::getInstructions() {
    return instructions;
}

Circle::~Circle() {

}
