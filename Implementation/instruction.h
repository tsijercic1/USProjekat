#include <vector>
#include <string>
#pragma once
class Instruction{
    std::string instructionName;
    std::vector<double> values;
    public:
    Instruction(){
        instructionName="";
    }
    Instruction(const Instruction& instruction){
        instructionName=instruction.instructionName;
        values = instruction.values;
    }
    void addValue(double value){
        values.push_back(value);
    }
    std::vector<double> getValues()const{
        return values;
    }
    std::string getInstructionName()const{
        return instructionName;
    }
    void setInstruction(std::string instructionName){
        instructionName=instructionName;
    }
};