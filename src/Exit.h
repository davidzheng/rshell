#ifndef __EXIT_H__
#define __EXIT_H__

#include "Command.h"

class Exit: public Command{
    public:
    Exit();
    virtual bool runCommand();
};

#endif
