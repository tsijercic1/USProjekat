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

class Interpreter {
    Head head;

public:
    void interpret(std::string line) {
        std::vector<std::string> tokens = tokenize(line, ' ');
        
        

    }
};