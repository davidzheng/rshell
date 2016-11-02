#ifndef __COMMAND_CPP__
#define __COMMAND_CPP__

#include <stdio.h>
#include <iostream>
#include <string>
#include <deque>
#include "Base.h"
#include "Command.h"
using namespace std;

Command::Command() {} // Default constructor

Command::Command(char* command){
    this->commandName  = command;
}

Command::Command(deque<char*>flagDeque){
    this->commandFlags = flagDeque;
}

Command::Command(char* command, deque<char*>flagDeque){
    this->commandName  = command;
    this->commandFlags = flagDeque;
}

void Command::addFlag(char* flag){
    commandFlags.push_back(flag);
}


#endif
