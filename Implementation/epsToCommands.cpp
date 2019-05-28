#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "CNC/instruction.h"
#include "epsparser.h"


int main(){
    EpsParser parser(std::string("./../DXF/b.eps"));
    // std::vector<Instruction>instructions = parser.getInstructions();
    return 0;
}