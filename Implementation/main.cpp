#include <iostream>
#include <string>
#include "interpreter.h"
#include <algorithm>
#include <cctype>
#include <locale>

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

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
