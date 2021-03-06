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

// Constructors
Command::Command() {} // Default constructor

Command::Command(char* cmdName){ // Constructor using a command as a parameter
    this->commandName  = cmdName;
    deque<char*> flags;
    this->commandFlags = flags;
}

// Member functions
void Command::addFlag(char* commandFlag){ // Adds flags to the command
    this->commandFlags.push_back(commandFlag);
}

bool Command::runCommand(){
    bool result = true; // Default result of the command is true

    //set up commmand and flags in argv
    char* argv[1000]; // Allocate space
    argv[0] = commandName; // Sets argv to commandName 
    int i = 1; // Counter needed to populate argv with flags
    while(!commandFlags.empty()){ // Add flags to argv
        argv[i] = commandFlags.front();
        commandFlags.pop_front();
        ++i;
    }
    argv[i] = NULL; // Ends argv with NULL

    int pid = fork();    
    if(pid == -1){ // Fork() returns -1 if it fails
        perror("problem with fork");
        exit(1);
    }
    else if(pid == 0){ // This is the child process if pid == 0
        if(execvp(argv[0], argv) == -1){ // Returns -1 if failure
            result = false; // Sets the result of the command to be false
            perror("problem with execvp");
            _exit(2); // Exit child process
        } 
        _exit(2);
    }
    if(pid > 0){ // This is the parent process 
        int status; // Int needed to pass into waitpid
        if(waitpid(pid, &status, 0) == -1){ // Waitpid forces parent to wait for child in order to stop zombie processes 
            perror("problem with waitpid"); // A return value of negative 1 indicates that waitpid was unsuccessful
        }
        if(WIFEXITED(status)){ // Checks if child terminated normally
            if(WEXITSTATUS(status) != 0){ // If exit status is not zero, set the bool of runCommand to be false  
                result = false;
            }
        }
    }
    return result; // Result is true unless otherwise noted
}

/*void Command::printCommand(){ // For testing purposes only
    cout << "Command Name: " << this->commandName << endl;
}*/

/*void Command::printFlags(){ // For testing purposes only
    for(unsigned i = 0; i < this->commandFlags.size(); ++i){
        cout << commandFlags.at(i) << "    ";
    }
    cout << endl;
}*/
#endif
