#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "instruction.h"
#pragma once

class EpsParser{
    std::vector<Instruction> instructions;
    bool isValidCharacter(char character){
        if(character>='a' && character<='z' || character>='A' && character<='Z' 
            || character>='0' && character<='9' || character=='-' || character == '\n' 
            || character==' ' || character=='+' || character=='.' )return true;

        return false;
    }
    bool isDigit(char character){
        if(character>='0' && character<='9')return true;
        return false;
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

        std::string instruction;
        while(!stream.eof()){
            char temp = stream.get();
            if(isValidCharacter(temp)){
                file.put(temp);
            }
        }
        stream.close();
        file.close();
        //file.open("./instructions.txt",std::ofstream::out);
        stream.open("./result.txt",std::ifstream::in);
        double value;
        std::string instructionName;
        while(!stream.eof()){
            
            Instruction instruction;
            //if(stream.peek()==10 || stream.peek()==32)std::cout<<stream.get();
            
            while(isDigit(stream.peek())){
                stream>>value;
                value/=2.8346457;
                instruction.addValue(value);
                if(stream.peek()==10 || stream.peek()==32)stream.get();
            }
            // stream>>instructionName;
            std::getline(stream,instructionName);
            instruction.setInstructionName(instructionName);
            instructions.push_back(instruction);
        }

        for(int i=0;i<instructions.size();i++){
            std::cout<<instructions[i].getInstructionName()<<" - ";
            for(double value : instructions[i].getValues()){
                std::cout<<value<<" ";
            }
            std::cout<<"\n";
        }
        file.close();
        stream.close();
        remove("./result.txt");
        // remove("./instructions.txt");
    }

    std::vector<Instruction> getInstructions()const{
        return instructions;
    }    
};