#pragma once

#include <vector>
#include <string>
#include <dirent.h>
#include <errno.h>

#include "epsparser.h"
#include "CNC/head.h"
#include "Geometry/polyline.h"
#include "Geometry/circle.h"
#include "Geometry/arc.h"

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
    
    return dir+filename;
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
    const char* errMissingArguments;
    const char* errUnkonwnCommand;
    const char* errBadCommandFormat;
    const char* errParsingDouble;
    const char* errUnknownShape;

    void execute(const std::vector<Instruction> &instuctions);
    void execute(const Instruction &instuction);
    void draw(std::vector<std::string> tokens);
    std::vector<Point> extractPointsFromTokens(std::vector<std::string> tokens, int numOfPoints = -1);
public:
    Interpreter() :
        errMissingArguments("Missing arguments!"),
        errUnknownShape("Unknown shape!"),
        errBadCommandFormat("Bad command format!"),
        errUnkonwnCommand("Unknown command!"),
        errParsingDouble("The entered value is not a number!") {}

    void interpret(std::string str);
    void interpretInstruction(std::string str);
    void interpretFile(std::string filePath);
};

void Interpreter::interpret(std::string str) {
    std::vector<std::string> tokens(tokenize(str));
    
    if(tokens.size() == 0)
        throw errMissingArguments;
    
    std::string command = tokens[0];
    
    if(command == "lineto" || command == "moveto") {
        interpretInstruction(str);
    }else if(command == "load") {
        std::string filename = fileLoader();
        interpretFile(filename);
    }else if(command == "draw") {
        std::vector<std::string> drawTokens(tokens.begin()+1, tokens.end());
        draw(drawTokens);
    }else {
        throw errUnkonwnCommand;
    }
}

void Interpreter::draw(std::vector<std::string> tokens) {
    if(tokens.size() == 0)
        throw errMissingArguments;
    
    std::string shapeName = tokens[0];

    if(shapeName == "line") {
        std::vector<std::string> pointTokens(tokens.begin()+1, tokens.end());
        std::vector<Point> points = extractPointsFromTokens(pointTokens);

        Polyline poly(points);
        execute(poly.getInstructions());
    }else if(shapeName == "circle") {
        if(tokens.size() != 4)
            throw errMissingArguments;
        
        double radius = 0;
        try {
            radius = std::stod(tokens[1]);
        }catch(...) {
            throw errParsingDouble;
        }

        if(radius <= 0)
            throw errBadCommandFormat;
        
        std::vector<std::string> pointTokens(tokens.begin()+2, tokens.end());
        std::vector<Point> points = extractPointsFromTokens(pointTokens, 1);
        
        Circle circle(points[0], radius);
        execute(circle.getInstructions());
    }else if(shapeName == "arc") {
        std::vector<std::string> pointTokens(tokens.begin()+1, tokens.end());
        std::vector<Point> points = extractPointsFromTokens(pointTokens, 4);

        Arc arc(points[0],points[1], points[2], points[3]);
        execute(arc.getInstructions());
    }else {
        throw errUnknownShape;
    }
}

std::vector<Point> Interpreter::extractPointsFromTokens(std::vector<std::string> tokens, int numOfPoints) {
    if(tokens.size() == 0)
        throw errMissingArguments;

    if(tokens.size() % 2 != 0)
        throw errBadCommandFormat;
    
    int numOfCoords = numOfPoints == -1 ? tokens.size() : numOfPoints * 2;

    if(numOfCoords != tokens.size())
        throw errBadCommandFormat;
    
    std::vector<Point> points;

    try {
        for(int i = 1; i < numOfCoords; i+=2) {
            double x = std::stod(tokens[i]);
            double y = std::stod(tokens[i+1]);
            points.push_back(Point(x, y));
        }
    }catch(...) {
        throw errParsingDouble;
    }

    return points;
}

void Interpreter::interpretInstruction(std::string str) {
    std::vector<std::string> tokens(tokenize(str, ' '));

    if(tokens.size() <= 0 || tokens.size() > 3)
            throw errBadCommandFormat;

    Instruction instruction;
    try {
        instruction.addValue(std::stod(tokens[0]));
        instruction.addValue(std::stod(tokens[1]));
        instruction.setInstructionName(tokens[2]);
    }catch(...) {
        throw errParsingDouble;
    }
    execute(instruction);
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

