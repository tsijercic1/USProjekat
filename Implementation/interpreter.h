#pragma once

#include <vector>
#include <string>
#include "CNC/head.h"

class Command {
public:
    char axis = 'x';
    double value = 0;

    Command(char axis = 'x', double value = 0):axis(axis),value(value) {}
    Command(const Command& command):axis(command.axis),value(command.value) {}
    Command(Command&& command):axis(command.axis),value(command.value) {}
    Command& operator=(Command&& command){
        axis = command.axis;
        value = command.value;
        return *this;
    }
    Command &operator=(const Command &command){
        axis = command.axis;
        value = command.value;
        return *this;
    }
};

class Interpreter {

    Head head;
    const char* errorMessage;
    Command parseCommand(std::string cmd);
    void setPointAxis(Command cmd, Point &point);
    void execute(const std::vector<Command> &commands);
    
public:
    Interpreter() : errorMessage("Komanda nije ispravnog formata!") {}
    void interpret(std::string line);
};
