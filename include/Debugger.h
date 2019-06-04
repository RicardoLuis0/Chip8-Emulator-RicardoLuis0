#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <vector>
#include <map>
#include <stdexcept>

#include "CPU.h"
#include "SDLHandlerDebug.h"
enum debug_command_enum{
    CMD_INVALID,//if invalid, first param is the whole string, second param is the error message
    CMD_EXIT,
    CMD_HELP,
    CMD_LOAD,
    CMD_START,
    CMD_STOP,
    CMD_STEP,
    CMD_CLEAR,
};

struct debug_command{
    debug_command_enum type;
    std::vector<std::string> args;
};


class Debugger {
    class UnclosedStringException:std::runtime_error{
        public:
            UnclosedStringException();
    };
    public:
        Debugger();
        void startDebug();
    protected:
        //commands
        void runCommand(debug_command cmd);
        void command_exit(std::vector<std::string> args);
        void command_help(std::vector<std::string> args);
        void command_load(std::vector<std::string> args);
        void command_start(std::vector<std::string> args);
        void command_stop(std::vector<std::string> args);
        void command_step(std::vector<std::string> args);
        void command_clear(std::vector<std::string> args);
        //misc
        bool running;
        static std::vector<std::string> splitCommand(std::string s);
        debug_command parseCommand(std::string str);
        CPU cpu;
        SDLHandlerDebug sdlhandler;
        static std::map<std::string,debug_command_enum> command_map;
        static std::map<debug_command_enum,void(Debugger::*)(std::vector<std::string> args)> command_fp_map;
    private:
};


#endif // DEBUGGER_H
