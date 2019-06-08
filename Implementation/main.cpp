#include<iostream>
#include<string>
#include "interpreter.h"
//#include <dirent.h>
//#include <errno.h>
//#include <vector>
#include "epsparser.h"
#include "./Geometry/circle.h"
#include "./Geometry/polyline.h"

/*
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
}*/


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
/*
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
    }*/
    
    Interpreter iper;
    /*
    std::string input;
    std::getline(std::cin, input);

    iper.interpretFile(input);
    */
    // Circle a(Point(-5,0) , 5);
    // iper.execute(a.getInstructions());
    // Polyline a({Point(0,0),Point(0.463,1.6),Point(1.434,2.559),Point(3,3),Point(4.617,2.527),Point(5.445,1.737),Point(5.939,0.599),Point(5.864,-0.892),Point(5.126,-2.116),Point(3.692,-2.919),Point(2.235,-2.9),Point(0.849,-2.091),Point(0.211,-1.107),Point(0,0)});
    // iper.execute(a.getInstructions());
    
    return 0;
}
