#ifndef __EXIT_CPP__
#define __EXIT_CPP__

#include <stdlib.h>
#include "Command.h"
#include "Exit.h"
using namespace std;

Exit::Exit(){}

bool Exit::runCommand(){
    exit(0);
}
#endif    
