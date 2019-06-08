#pragma once

#include <vector>
#include <string>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include "CNC/head.h"
#include "epsparser.h"
#include "Geometry/polyline.h"

int getdir (std::string dir, std::vector<std::string> &files) {
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        std::cout << "Error(" << errno << ") opening " << dir << std::endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(std::string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

std::string fileLoader() {
    std::string dir = std::string("./../Import/");
    std::vector<std::string> files;

    getdir(dir,files);
    std::cout<<"Files: \n";
    for (unsigned int i = 2;i < files.size();i++) {
        std::cout << "\t" << files[i] << std::endl;
    }
    std::string filename;
    std::cout<<"Enter file name: ";
    std::getline(std::cin, filename);
    bool isFound = false;
    for (unsigned int i = 2;i < files.size();i++) {
        if(files[i]==filename){
            isFound = true;
        }
    }
    if (!isFound)
        throw "File not found!";
    
    return filename;
}

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
    Interpreter() : errorMessage("Wrong command format!") {}
    void interpret(std::string line);
    void interpretInstruction(std::string line);
    void interpretFile(std::string filePath);
    void execute(const std::vector<Instruction> &instuctions);
    void execute(const Instruction &instuction);
};

void Interpreter::interpret(std::string line) {
    std::vector<std::string> tokens(tokenize(line, ' '));
    
    if(tokens.size() == 0)
        throw errorMessage;
    
    std::string command = tokens[0];
    
    if(command == "lineto" || command == "moveto") {
        interpretInstruction(line);
    }else if(command == "load") {
        std::string filename = fileLoader();
        interpretFile(filename);
    }else if(command == "draw") {
        std::string shapeName = tokens[1];
        
        if(shapeName == "line") {
            
            // Napravi da se svake dvije tacke uzima point i dodaje u points, a ne double....
            
            std::vector<double> points;
            for(int i = 3; i < tokens.size(); i++) {
                points.push_back(std::stod(tokens[i]));
            }
            Polyline poly(points);
        }else if(shapeName == "circle") {
        
        }else {
            throw "Unknown shape!";
        }
        
    }else {
        throw "Unknown command!";
    }
}

void Interpreter::interpretInstruction(std::string line) {
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

