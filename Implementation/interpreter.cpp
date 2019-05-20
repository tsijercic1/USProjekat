#include<iostream>
#include "head.h"

int main() {
    Head head;

    while(true) {
        if(head.isAvailable()) {
            std::string input;
            std::cin >> input;
            Point p(2, 4);
            head.lineTo(p);
        }
    }

    return 0;
}