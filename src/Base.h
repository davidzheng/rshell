#ifndef __BASE_H__
#define __BASE_H__

using namespace std;

class Base{
    public:
        virtual bool runCommand() = 0;
        //virtual void printCommand() = 0; // For testing purposes
};

#endif

