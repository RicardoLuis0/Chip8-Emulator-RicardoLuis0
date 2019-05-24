#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "CPU.h"

class Debugger {
    public:
        Debugger(CPU cpu);
        void startDebug();
    protected:
        CPU cpu;

    private:
};

#endif // DEBUGGER_H
