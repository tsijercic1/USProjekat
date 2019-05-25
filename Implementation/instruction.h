#include <vector>
#include <string>
#pragma once
class Instruction{
    private:
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
    
    Instruction(Instruction&& instruction):instructionName(std::move(instruction.instructionName)),values(std::move(instruction.values)){};

    Instruction& operator = (const Instruction& instruction) = default;

    void addValue(double value){
        values.push_back(value);
    }
    std::vector<double> getValues()const{
        return values;
    }
    std::string getInstructionName()const{
        return instructionName;
    }
    void setInstructionName(std::string instructionName){
        this->instructionName=instructionName;
    }

};