#pragma once

#include <vector>
#include <string>
#include "head.h"

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

struct Command {
    char axis = 'x';
    double value = 0;
};

class Interpreter {
    
    
    Head head;
    const char* errorMessage;
    
    Command parseCommand(std::string cmd) {
        char axis = cmd[0];
        std::string value = cmd.substr(1);
        
        Command command;
        
        try{
            if(axis != 'x' && axis != 'y' && axis != 'z')
                throw;
            
            command = {axis, std::stod(value)};
        }catch(...){
            throw errorMessage;
        }
        
        return command;
    }
    
    void setPointAxis(Command cmd, Point &point) {
        switch(cmd.axis) {
            case 'x':
                point.x = cmd.value;
                break;
            case 'y':
                point.y = cmd.value;
                break;
            case 'z':
                break;
            default: 
                throw errorMessage;
        }
    }
    
    void execute(const std::vector<Command> &commands) {
        Point target;
        bool write = false;
        
        for(int i = 0; i < commands.size(); i++) {
            Command cmd = commands[i];
            
            setPointAxis(cmd, target);
            if(cmd.axis == 'z') {
                write = cmd.value <= 0;
            }
        }
        
        if(head.isAvailable()) {
            std::cout << "Available..." << std::endl;
            std::cout << "x: " << target.x << " y: " << target.y << std::endl; 
            if(write)
                head.lineTo(target);
            else
                head.moveTo(target);
            
            while(!head.isAvailable());
        }
        
    }
    
public:
    Interpreter() : errorMessage("Komanda nije ispravnog formata!") {}

    void interpret(std::string line) {
        std::vector<std::string> tokens(tokenize(line, ' '));
        
        if(tokens.size() > 3)
            throw errorMessage;
        
        std::vector<Command> commands(3);
        
        for(int i = 0; i < tokens.size(); i++) {
            Command cmd = parseCommand(tokens[i]);
            commands[i] = cmd;
        }
        
        execute(commands);
    }
};
