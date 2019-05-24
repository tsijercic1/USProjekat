#include<iostream>
#include "interpreter.h"

int main() {
    //Interpreter interpreter;
    //Head head;

    bool isDown = false;
    /*while(true) {
        if(head.isAvailable()) {
            if(isDown)
                head.moveTo(head.getPosition());
            else
                head.lineTo(head.getPosition());

            isDown = !isDown;
        }
    }*/
    
    /*Motor zAxis(7, 11, 13, 15, 4096*2);
    
    for(int i = 0; i < 4096; i++) {
        zAxis.step(1);
        delayMicroseconds(680);
    }*/
    
    Head head;
    while(!head.isAvailable());
    if(head.isAvailable()) {
        std::cout << "Available" << std::endl;
        head.moveTo({0,20});    
    }

    return 0;
}
