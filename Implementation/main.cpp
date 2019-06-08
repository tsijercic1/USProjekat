#include <iostream>
#include <string>
#include "interpreter.h"
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <map>
#include <functional>


int getdir (std::string dir, std::vector<std::string> &files) {
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

std::string fileLoader() {
    std::string dir = std::string("./../Import/");
    std::vector<std::string> files;

    getdir(dir,files);
    std::cout<<"Files: \n";
    for (unsigned int i = 2;i < files.size();i++) {
        std::cout << "\t" << files[i] << std::endl;
    }
    std::string filename;
    std::cout<<"Enter file name: ";
    std::getline(std::cin, filename);
    bool isFound = false;
    for (unsigned int i = 2;i < files.size();i++) {
        if(files[i]==filename){
            std::cout << "File found!\n";
            isFound = true;
        }
    }
    if (!isFound)
        throw "File not found!";
    
    return filename;
}

void help() {
    
}

void load() {
    
}

void moveto() {
    
}

void lineto() {
    
}

void draw() {
    
}

int main() {
    std::map<std::string, std::function<void()>> actions;
    
    
    
    return 0;
}
