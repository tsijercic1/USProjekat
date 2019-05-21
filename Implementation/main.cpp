#include<iostream>
#include<string>
#include "interpreter.h"

struct Strakt{
    double d;
    char c;
};

int main() {
    /*
    Head head;
    while(!head.isAvailable());
    if(head.isAvailable()) {
        std::cout << "Available" << std::endl;
        head.moveTo({0,20});    
    }*/
    
    Interpreter interpreter;
    
    std::string line;
    std::getline(std::cin, line);
    
    try{
        interpreter.interpret(line);
    }catch(const char* msg) {
        std::cout << msg << std::endl;
    }

    return 0;
}
