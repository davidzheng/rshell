#ifndef __TEST_H__
#define __TEST_H__

#include "Command.h"
using namespace std;

class TEST: public Command{
    protected:
        char* testCommand;
        deque<char*> commandFlags;
    public:
        TEST();
        void addFlag(char* commandFlag);
        bool runCommand();
};

#endif
