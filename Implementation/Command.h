#include <vector>
#include <string>

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
    void setCommand(std::string command){
        commandName=command;
    }
};