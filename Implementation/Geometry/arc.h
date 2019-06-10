#pragma once

#include <vector>
#include "point.h"
#include "shape.h"
#include "./../CNC/instruction.h"

class Arc : public Shape {
    Point zero,one,two,three;
    Point A,B,C;
    std::vector<Instruction> instructions;

    double calculateCoefficientA(double a0, double a1, double a2, double a3);
    double calculateCoefficientB(double a0, double a1, double a2, double a3);
    double calculateCoefficientC(double a0, double a1, double a2, double a3);
    void calculateCoefficients();
    public:
    Arc(Point zero, Point one, Point two, Point three);
    Arc(const Arc& arc);
    double getX(double t);
    double getY(double t);
    Point getPoint(double t);
    std::vector<Instruction> Arc::getInstructions() {
        return instructions;
    }
};


double Arc::calculateCoefficientA(double a0, double a1, double a2, double a3){
    return a3-a0-calculateCoefficientC(a0,a1,a2,a3)-calculateCoefficientB(a0,a1,a2,a3);
}

double Arc::calculateCoefficientB(double a0, double a1, double a2, double a3){
    return 3*(a2-2*a1+a0);
}

double Arc::calculateCoefficientC(double a0, double a1, double a2, double a3){
    return 3*(a1-a0);
}

void Arc::calculateCoefficients(){
    A.x=calculateCoefficientA(zero.x,one.x,two.x,three.x);
    A.y=calculateCoefficientA(zero.y,one.y,two.y,three.y);
    B.x=calculateCoefficientB(zero.x,one.x,two.x,three.x);
    B.y=calculateCoefficientB(zero.y,one.y,two.y,three.y);
    C.x=calculateCoefficientC(zero.x,one.x,two.x,three.x);
    C.y=calculateCoefficientC(zero.y,one.y,two.y,three.y);
}

Arc::Arc(Point zero, Point one, Point two, Point three):zero(zero),one(one),two(two),three(three){
    calculateCoefficients();
}

Arc::Arc(const Arc& arc):Arc(arc.zero,arc.one,arc.two,arc.three){}

double Arc::getX(double t){
    if(t<0 || t>1)
        throw "Nekorektan parametar t!\n";
    return A.x*t*t*t+B.x*t*t+C.x*t+zero.x;
}
double Arc::getY(double t){
    if(t<0 || t>1)
        throw "Nekorektan parametar t!\n";
    return A.y*t*t*t+B.y*t*t+C.y*t+zero.y;
}

Point Arc::getPoint(double t){
    return Point(getX(t),getY(t));
}