#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include "instruction.h"
#include "bezier.h"
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
    void interpolate(){
        std::vector<Instruction> newInstructions;
        for(int i=0;i<instructions.size();i++){
            if(instructions[i].getInstructionName()=="curveto"){
                double distance = sqrt(pow(instructions[i].getValues()[4]-instructions[i].getValues()[0],2)+pow(instructions[i].getValues()[5]-instructions[i].getValues()[1],2));
                double step = 1./distance;
                Bezier bezier(Point(newInstructions[newInstructions.size()-1].getValues()[0],newInstructions[newInstructions.size()-1].getValues()[1]),
                                Point(instructions[i].getValues()[0],instructions[i].getValues()[1]),
                                Point(instructions[i].getValues()[2],instructions[i].getValues()[3]),
                                Point(instructions[i].getValues()[4],instructions[i].getValues()[5]));
                for(int j=1;j*step<1;j++){
                    Instruction instruction;
                    instruction.setInstructionName("lineto");
                    instruction.addValue(bezier.getX(j*step));
                    instruction.addValue(bezier.getY(j*step));
                    newInstructions.push_back(instruction);
                }
                Instruction instruction;
                instruction.setInstructionName("lineto");
                instruction.addValue(bezier.getX(1));
                instruction.addValue(bezier.getY(1));
                newInstructions.push_back(instruction);
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
        interpolate();
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