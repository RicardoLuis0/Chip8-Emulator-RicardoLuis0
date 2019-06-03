#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <vector>

#include "CPU.h"
#include "SDLHandlerDebug.h"
enum debug_command_enum{
    CMD_INVALID,//if invalid, first param is the whole string, second param is the error message
    CMD_EXIT,
};

struct debug_command{
    debug_command_enum command;
    std::vector<std::string> params;
};

class Debugger {
    public:
        Debugger();
        void startDebug();
    protected:
        //commands
        void exitDebug();
        //misc
        static std::vector<std::string> splitCommand(std::string s);
        debug_command parseCommand(std::string str);
        CPU cpu;
        SDLHandlerDebug sdlhandler;
    private:
};


#endif // DEBUGGER_H
