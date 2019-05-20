#include<iostream>
#include "interpreter.h"

int main() {
    Interpreter interpreter;

    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = tokenize(input, ' ');

    for(std::string s : tokens) {
        std::cout << "'" << s << "'" << std::endl;
    }

    return 0;
}