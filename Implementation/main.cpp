#include <iostream>
#include <string>
#include "trim.h"
#include "interpreter.h"
#include <algorithm>
#include <cctype>
#include <locale>

int main() {
    Interpreter interpreter;
    
    while(true) {
        try {
            std::string input;
            std::getline(std::cin, input);
            trim(input);

            if(input.empty())
                continue;
            
            if(input == "exit")
                break;
            
            interpreter.interpret(input);
        }catch(const char* errMsg) {
            std::cout << "Error: " << errMsg << std::endl;
        }
    }
    
    return 0;
}
