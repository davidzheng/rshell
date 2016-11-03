#ifndef __EXIT_CPP__
#define __EXIT_CPP__

#include "Command.h"
#include "Exit.h"

Exit::Exit(){}

bool Exit::runCommand(){
    exit(1);
}

#endif
