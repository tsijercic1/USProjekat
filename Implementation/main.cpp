#include <iostream>
#include <string>
#include "interpreter.h"


int main() {
    Interpreter interpreter;
    
    while(true) {
        std::string input;
        std::getline(std::cin, input);
        
        if(input == "exit")
            break;
        
        interpreter.interpret(input);
    }
    
    return 0;
}
