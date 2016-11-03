#ifndef __COMMAND_CPP__
#define __COMMAND_CPP__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <deque>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "Base.h"
#include "Command.h"
using namespace std;

Command::Command() {} // Default constructor

Command::Command(char* cmdName){
    this->commandName  = cmdName;
    deque<char*> temp;
    this->commandFlags = temp;
}

Command::Command(deque<char*>cmdFlags){
    this->commandFlags = cmdFlags;
}

Command::Command(char* command, deque<char*>flagDeque){
    this->commandName  = command;
    this->commandFlags = flagDeque;
}

void Command::addFlag(char* commandFlag){
    this->commandFlags.push_back(commandFlag);
}

bool Command::runCommand(){
    bool result = true;

    //set up commmand and flags in argv
    char* argv[1000];
    int i = 1;
    argv[0] = commandName;
    while(!commandFlags.empty()){
        argv[i] = commandFlags.front();
        commandFlags.pop_front();
        ++i;
    }


    int pid = fork();
    if(pid == -1){
        perror("problem with fork");
        exit(1);
    }
    else if(pid == 0){ // This is the child process if pid == 0
        if(execvp(argv[0], argv) == -1){ // Returns -1 if failure
            result = false;
            perror("problem with execvp");
            exit(1);
        } 
        _exit(2);
    }
    if(pid > 0){ // This is the parent process 
        int status;
        if(waitpid(pid, &status, 0) == -1){ // Waitpid forces parent to wait for child in order to stop zombie processes. 
            perror("problem with waitpid"); // A return value of negative 1 indicates that waitpid was unsuccessful
        }
        if(WIFEXITED(status)){ // Was child terminated normally?
            if(WEXITSTATUS(status) != 0){ // If exit status is not zero, set the bool of runCommand to be false.
                result = false;
            }
        }
    }
    return result;
}

void Command::printCommand(){
    cout << "Command Name: " << this->commandName << endl;
}

void Command::printFlags(){
    for(unsigned i = 0; i < this->commandFlags.size(); ++i){
        cout << commandFlags.at(i) << "    ";
    }
    cout << endl;
}
#endif