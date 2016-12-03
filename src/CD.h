#ifndef __CD_H__
#define __CD_H__

#include "Command.h"
using namespace std;

class CD: public Base{
    protected:
        deque<char*> cdFlags;
    public:
        CD();
        void addFlag(char* commandFlag);
        bool runCommand();
};

#endif
