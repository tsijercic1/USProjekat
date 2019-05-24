#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Command.h"

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

int main(){
    std::vector<Command> commands;
    std::ifstream stream;
    std::string x;
    stream.open("./../DXF/b.eps",std::ifstream::in);
    std::ofstream file;
    file.open("./../DXF/result.txt",std::ofstream::out);
    while(stream.peek()=='%' || stream.peek()=='\n'){
        std::getline(stream,x);
    } 

    std::string command;
    while(!stream.eof()){
        char temp = stream.get();
        if(isValidCharacter(temp)){
            file.put(temp);
        }
    }
    stream.close();
    file.close();
    file.open("./../DXF/commands.txt",std::ofstream::out);
    stream.open("./../DXF/result.txt",std::ifstream::in);
    double value;
    std::string commandName;
    while(!stream.eof()){
        Command command;
        if(stream.peek()==10 || stream.peek()==32)stream.get();
        
        //std::cout<<(char)stream.peek()<<"--";
        while(isDigit(stream.peek())){
            stream>>value;
            value/=2.8346457;
            command.addValue(value);
            if(stream.peek()==10 || stream.peek()==32)stream.get();
        }
        stream>>commandName;
        command.setCommand(commandName);
        commands.push_back(command);
    }

    for(int i=0;i<commands.size();i++){
        std::cout<<commands[i].getCommandName()<<" ";
        for(double value : commands[i].getValues()){
            std::cout<<value<<" ";
        }
        std::cout<<"\n";
    }
    return 0;
}