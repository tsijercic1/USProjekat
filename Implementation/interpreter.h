#pragma once

#include <vector>
#include <string>
#include "CNC/head.h"
#include "epsparser.h"

std::vector<std::string> tokenize(std::string str, char delimiter = ' ') {
    std::vector<std::string> tokens;

    size_t lPos = 0;
    size_t pos = 0;

    while((pos = str.find(delimiter, lPos)) != std::string::npos) {
        std::string res = str.substr(lPos, pos - lPos);
        if(!res.empty())
            tokens.push_back(res);
        lPos = pos + 1;
    }
    std::string res = str.substr(lPos);
    if(!res.empty())
        tokens.push_back(res);

    return tokens;
}

class Interpreter {
    Head head;
    const char* errorMessage;
public:
    Interpreter() : errorMessage("Komanda nije ispravnog formata!") {}
    void interpret(std::string line);
    void interpretFile(std::string filePath);
    void execute(const std::vector<Instruction> &instuctions);
    void execute(const Instruction &instuction);
};

void Interpreter::interpret(std::string line) {
    std::vector<std::string> tokens(tokenize(line, ' '));

    if(tokens.size() <= 0 || tokens.size() > 3)
            throw errorMessage;

    try {
        Instruction instruction;
        instruction.addValue(std::stod(tokens[0]));
        instruction.addValue(std::stod(tokens[1]));
        instruction.setInstructionName(tokens[2]);
        
        execute(instruction);
    }catch(...) {
        throw errorMessage;
    }
}

void Interpreter::interpretFile(std::string filePath) {
    EpsParser parser(filePath);
    for(Instruction element : parser.getInstructions()){
        execute(element);
    }
}

void Interpreter::execute(const Instruction &instruction) {
    std::string name = instruction.getInstructionName();
    Point target;
    
    if(name == "moveto" || name == "lineto") {
        target.x = instruction.getValues()[0];
        target.y = instruction.getValues()[1];
    } else {
        target = head.getPosition();
    }
    
    if(head.isAvailable()) {
        std::cout << name << " - x: " << target.x << " y: " << target.y << std::endl;
        if(name == "lineto")
            head.lineTo(target);
        else
            head.moveTo(target);

        while(!head.isAvailable());
    }
}

void Interpreter::execute(const std::vector<Instruction> &instructions) {
    for(Instruction instruction : instructions) {
        execute(instruction);
    }
}

