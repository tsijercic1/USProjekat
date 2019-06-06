//
// Created by tsijercic1 on 5/27/19.
//
#pragma once
#include <vector>
#include "point.h"
#include "../CNC/instruction.h"
#include <initializer_list>

class Polyline:public Shape{
    std::vector<Point> points;
    std::vector<Instruction> instructions;

    void convertToInstructions(){
        Instruction instruction;
        instruction.setInstructionName("moveto");
        instruction.addValue(points[0].x);
        instruction.addValue(points[0].y);
        instructions.push_back(instruction);
        for(int i=1;i<points.size();i++){
            Instruction instruction1;
            instruction1.setInstructionName("lineto");
            instruction1.addValue(points[i].x);
            instruction1.addValue(points[i].y);
            instructions.push_back(instruction1);
        }
        Instruction instruction2;
        instruction2.setInstructionName("stroke");
        instructions.push_back(instruction2);
    }
public:
    Polyline(std::initializer_list<Point> points):points(points){
        convertToInstructions();
    }

    std::vector<Instruction> getInstructions(){
        return instructions;
    }
};
