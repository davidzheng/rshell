#ifndef __EXIT_H__
#define __EXIT_H__

#include "Command.h"
using namespace std;

class Exit: public Command{
    public:
        // Constructors
        Exit();
        // Member functions
        bool runCommand();
};

#endif
