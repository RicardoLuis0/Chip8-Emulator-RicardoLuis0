#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <atomic>
#include <mutex>
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
        void readCommandThread();
        debug_command parseCommand(std::string str);
        CPU cpu;
        SDLHandlerDebug sdlhandler;
        debug_command last_command;
        std::atomic<bool> run_thread;
        std::atomic<bool> is_command_pending;
        std::mutex command_mutex;
        friend void thread_entrypoint(Debugger * data);
    private:
};


#endif // DEBUGGER_H
