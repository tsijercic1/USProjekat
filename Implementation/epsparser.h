#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include "CNC/instruction.h"
#include "Geometry/arc.h"
#pragma once

class EpsParser{
    std::vector<Instruction> instructions;
    bool isValidCharacter(char character){
        if(character>='a' && character<='z' || character>='A' && character<='Z' 
            || character>='0' && character<='9' || character=='-' 
            || character==' ' || character=='+' || character=='.' )return true;

        return false;
    }
    bool isDigit(char character){
        if(character>='0' && character<='9')return true;
        return false;
    }
    void interpolate(){
        std::vector<Instruction> newInstructions;
        for(int i=0;i<instructions.size();i++){
            if(instructions[i].getInstructionName()=="curveto"){
                Arc arc(Point(newInstructions[newInstructions.size()-1].getValues()[0],newInstructions[newInstructions.size()-1].getValues()[1]),
                                Point(instructions[i].getValues()[0],instructions[i].getValues()[1]),
                                Point(instructions[i].getValues()[2],instructions[i].getValues()[3]),
                                Point(instructions[i].getValues()[4],instructions[i].getValues()[5]));
                for(Instruction element : arc.getInstructions()){
                    newInstructions.push_back(element);
                }
                
            }else{
                newInstructions.push_back(instructions[i]);
            }
        }
        instructions=newInstructions;
    }
public:
    EpsParser(std::string filePath){
        std::ifstream stream;
        std::string x;
        stream.open(filePath,std::ifstream::in);
        std::ofstream file;
        file.open("./result.txt",std::ofstream::out);
        while(stream.peek()=='%' ){
            std::getline(stream,x);
        } 
        
        while(!stream.eof()){
            std::getline(stream,x);
            if(x != ""){
                std::string s = x;
                std::string delimiter = " ";
                size_t pos = 0;
                std::string token;
                Instruction instruction;
                while ((pos = s.find(delimiter)) != std::string::npos) {
                    token = s.substr(0, pos);
                    double value = std::stod(token);
                    value/=2.8346457;
                    instruction.addValue(value);
                    s.erase(0, pos + delimiter.length());
                }
                instruction.setInstructionName(s);
                instructions.push_back(instruction);
            }
        }
        stream.close();
        file.close();
        interpolate();
    }

    std::vector<Instruction> getInstructions()const{
        return instructions;
    }    
};
