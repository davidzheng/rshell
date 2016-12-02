#ifndef __CD_CPP__
#define __CD_CPP__

#include <deque>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include "Base.h"
#include "CD.h"
using namespace std;

CD::CD(){}

bool CD::runCommand(){
    if(cdFlags.size() == 0){ // cd without any modifiers
        char* homeDirectory = getenv("HOME");
        char* prevDirectory = getenv("PWD");
        if(homeDirectory == NULL || prevDirectory == NULL){
            perror("getenv");
        } 
        if(chdir(homeDirectory) == -1){ // Attempts to change the current directory to home and checks if successful
            perror("chdir to home unsuccessful");
        }
        else{ // Change was successful
            if(setenv("OLDPWD", prevDirectory, 1) == -1){ // Checks if setenv oldpwd to previous directory was successful
                perror("setenv OLDPWD unsuccessful");
            }
            if(setenv("PWD", homeDirectory, 1) == -1){ // Checks if setevn pwd to home directory was successful
                perror("setenv PWD unsuccessful");
            }
            return true; // Passed all checks for errors
        }
    }
    else{ // cd with modifiers
        char* directoryPath = cdFlags.front(); // Takes the saved modifier and stores it in target directory path
        char* prevDirectory = getenv("PWD"); // Stores the previous directory
        if(prevDirectory == NULL){ // Checks if previous directory exists
            perror("getenv");
        }
        if(strcmp(directoryPath, "-") == 0){ // Checks if the modifier is the special case "-"
            directoryPath = getenv("OLDPWD"); // If special case is detected, sets the target path to oldpwd
            if(directoryPath == NULL){ // Checks if old path exists
                perror("OLDPWD not set");
            }
        }
        //cout << directoryPath << endl; // For testing purposes only
        if(chdir(directoryPath) == -1){ // Attempts to change the current directory to the target path and checks if successful
            perror("chdir to target unsuccessful");
        }
        else{ // chdir was successful
            char* currentDirectory = getenv("PWD"); // Gets actual pwd 
            if(setenv("PWD", currentDirectory, 1) == -1){ // Sets pwd to current directory and checks if successful
                perror("setenv PWD unsuccessful");
            }
            if(setenv("OLDPWD", prevDirectory, 1) == -1){ // Sets oldpwd to previous directory
                perror("setenv OLDPWD unsuccessful");
            }
        }
    }
    return true;
}

void CD::addFlag(char* commandFlag){
    cdFlags.push_back(commandFlag);
}

#endif
