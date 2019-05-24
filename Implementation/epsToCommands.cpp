#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class Command{
    std::string commandName;
    std::vector<double> values;
    public:
    Command(){
        commandName="";
    }
    Command(const Command& command){
        commandName=command.commandName;
        values = command.values;
    }
    void addValue(double value){
        values.push_back(value);
    }
    std::vector<double> getValues()const{
        return values;
    }
    std::string getCommandName()const{
        return commandName;
    }
};

bool isValidCharacter(char character){
    if(character>='a' && character<='z' || character>='A' && character<='Z' 
        || character>='0' && character<='9' || character=='-' || character == '\n' 
        || character==' ' || character=='+' || character=='.' )return true;

    return false;
}

int main(){
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
    double x,y;
    std::string command;
    while(!stream.eof()){

    }

    return 0;
}