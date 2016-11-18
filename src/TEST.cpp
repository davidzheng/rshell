#ifndef __TEST_CPP__
#define __TEST_CPP__

#include <iostream>
#include <deque>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include "Base.h"
#include "TEST.h"
using namespace std;

TEST::TEST(){}

void TEST::addFlag(char* commandFlag){
    commandFlags.push_back(commandFlag);
}

bool TEST::runCommand(){ // -e -f -d
    struct stat statBuffer;
    char* flag;
    char* filePath;
    bool testResult = true;
    /*for(int i = 0; i < commandFlags.size(); ++i){
        cout << commandFlags.at(i) << endl;
    }*/
    if(commandFlags.size() == 2){ // Test inputs should be a flag(-e, -f, or -d) and a filepath
        flag = commandFlags.front(); // The front of commandFlags should be the flag
        commandFlags.pop_front(); // Removes the flag from the deque
        filePath = commandFlags.front(); // Sets filePath to the one stored in deque
        commandFlags.pop_front(); // Removes the flag from the deque
    }
    else if (commandFlags.size() == 1){
        string defaultFlag = "-e";
        char* c_defaultFlag = new char[3];
        strcpy(c_defaultFlag, defaultFlag.c_str());
        commandFlags.push_front(c_defaultFlag);
        flag = commandFlags.front();
        commandFlags.pop_front();
        filePath = commandFlags.front();
        commandFlags.pop_front();
    }
    else{ // Invalid input if the size of commandFlags is not 2
        perror("Invalid test inputs");
        return false;
    }
    if(strcmp(flag, "-e") == 0 || strcmp(flag, "-f") == 0 || strcmp(flag, "-d") == 0){ // Checks if flag is valid
        if(stat(filePath, &statBuffer) == 0){ // Stat function for the filePath and stores in statBuffer
            if(strcmp(flag, "-f") == 0){ // Checks if filePath points to a register
                testResult = S_ISREG(statBuffer.st_mode);
            }
            else if(strcmp(flag, "-d") == 0){ // Checks if filePath points to a directory
                testResult = S_ISDIR(statBuffer.st_mode);
            }
        }    
        else{ // The -e flag is true unless the stat function returns false
            testResult = false;
        }        
    }
    else{ // Flag is invalid
        perror("Invalid flag");
        return false;
    }
    if(testResult){ // Output if true
        cout << "(True)" << endl;
        return true;
    }
    else{ // Output if false
        cout << "(False)" << endl;
        return false;
    }
}
#endif
