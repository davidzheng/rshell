#ifndef __COMMAND_CPP__
#define __COMMAND_CPP__

#include <stdio.h>
#include <iostream>
#include <string>
#include <deque>
#include "Base.h"
#include "Command.h"
#include <iostream>
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
    return true;
}

void Command::printCommand(){
    cout << "Command Name: " << this->commandName << endl;
}

void Command::printFlags(){
    for(int i = 0; i < this->commandFlags.size(); ++i){
        cout << commandFlags.at(i) << "    ";
    }
    cout << endl;
}
#endif
