#ifndef __EXIT_CPP__
#define __EXIT_CPP__

#include <stdlib.h>
#include "Command.h"
#include "Exit.h"
using namespace std;

// Constructors
Exit::Exit(){}

// Member funcions
bool Exit::runCommand(){ // Simply exits the program
    exit(0);
}

#endif    
