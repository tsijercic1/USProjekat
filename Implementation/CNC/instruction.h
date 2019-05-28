#include <vector>
#include <string>
#pragma once

class Instruction{
    private:
    std::string instructionName;
    std::vector<double> values;
    public:
    Instruction();
    Instruction(const Instruction& instruction);
    Instruction(Instruction&& instruction);
    Instruction& operator = (const Instruction& instruction) = default;
    void addValue(double value);
    std::vector<double> getValues()const;
    std::string getInstructionName()const;
    void setInstructionName(std::string instructionName);
};


Instruction::Instruction(){
    instructionName="";
}

Instruction::Instruction(const Instruction &instruction) {
    instructionName=instruction.instructionName;
    values = instruction.values;
}

Instruction::Instruction(Instruction &&instruction) :instructionName(std::move(instruction.instructionName)),
                                                     values(std::move(instruction.values)){};

void Instruction::addValue(double value) {
    values.push_back(value);
}

std::vector<double> Instruction::getValues()const{
    return values;
}

std::string Instruction::getInstructionName() const {
    return instructionName;
}

void Instruction::setInstructionName(std::string instructionName){
    this->instructionName = instructionName;
}
