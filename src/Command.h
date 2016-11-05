#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <deque>
#include "Base.h"
using namespace std;

class Command: public Base{
    protected:
        deque<char*> commandFlags;
        char* commandName;
    public:
        Command();
        Command(char* cmdName);
        Command(deque<char*>cmdFlags);
        Command(char* cmdName, deque<char*>cmdFlags);
        virtual bool runCommand();
        void addFlag(char* commandFlag);
//        void printCommand(); // For testing purposes only
//        void printFlags();
};
#endif
