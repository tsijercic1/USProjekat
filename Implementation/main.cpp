#include<iostream>
#include "interpreter.h"

int main() {
    Interpreter interpreter;
    Head head;

    std::string input;
    std::getline(std::cin, input);

    bool isDown = false;
    while(true) {
        if(head.isAvailable()) {
            if(isDown)
                head.moveTo(head.getPosition());
            else
                head.lineTo(head.getPosition());

            isDown = !isDown;
        }

        std::cin.get();
    }

    return 0;
}