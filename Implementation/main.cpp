#include<iostream>
#include<string>
//#include "interpreter.h"
#include <dirent.h>
#include <errno.h>
#include <vector>
#include "epsparser.h"


struct Strakt{
    double d;
    char c;
};

int getdir (std::string dir, std::vector<std::string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        std::cout << "Error(" << errno << ") opening " << dir << std::endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(std::string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}


int main() {
    /*
    Head head;
    while(!head.isAvailable());
    if(head.isAvailable()) {
        std::cout << "Available" << std::endl;
        head.moveTo({0,20});    
    }*/
    
//    Interpreter interpreter;
//
//    std::string line;
//    std::getline(std::cin, line);
//
//    try{
//        interpreter.interpret(line);
//    }catch(const char* msg) {
//        std::cout << msg << std::endl;
//    }
    std::string dir = std::string("./../Import/");
    std::vector<std::string> files;

    getdir(dir,files);
    std::cout<<"Fajlovi na raspolaganju: \n";
    for (unsigned int i = 2;i < files.size();i++) {
        std::cout << "\t" << files[i] << std::endl;
    }
    std::string filename;
    while (true) {
        std::cout<<"Unesite ime fajla za crtanje:";
        std::getline(std::cin, filename);
        if(filename=="exit")break;
        bool isFound = false;
        for (unsigned int i = 2;i < files.size();i++) {
            if(files[i]==filename){
                std::cout << "File found!\n";
                isFound = true;
            }
        }
        if (!isFound) {
            std::cout << "File not found!\n";
        }else{
            std::cout<<"Executing instructions from file : "<<filename<<std::endl<<std::endl;
            EpsParser parser("./../Import/"+filename);
            for(Instruction element : parser.getInstructions()){
                std::cout<<element.getInstructionName()<<"\t";
                if (element.getValues().size()>1) {
                    std::cout << element.getValues().at(0) << "\t" << element.getValues().at(1);
                }
                std::cout << std::endl;
            }
        }

    }
    return 0;
}
