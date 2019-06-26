#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <vector>
#include <set>
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
    CMD_RAMDUMP,
    CMD_VRAMDUMP,
    CMD_EXEC_SP,
    CMD_BREAK,
    CMD_READ_REGISTERS,
    CMD_PEEK,
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
        static uint32_t read_num(std::string);//throws
        //commands
        void runCommand(debug_command cmd);
        void command_exit(std::vector<std::string> args);
        void command_help(std::vector<std::string> args);
        void command_load(std::vector<std::string> args);
        void command_start(std::vector<std::string> args);
        void command_stop(std::vector<std::string> args);
        void command_step(std::vector<std::string> args);
        void command_clear(std::vector<std::string> args);
        void command_ramdump(std::vector<std::string> args);
        void command_vramdump(std::vector<std::string> args);
        void command_exec_sp(std::vector<std::string> args);
        void command_exec(std::vector<std::string> args);
        void command_break(std::vector<std::string> args);
        void command_read_registers(std::vector<std::string> args);
        void command_peek(std::vector<std::string> args);
        //misc
        bool running;
        bool justresumed;
        static std::vector<std::string> splitCommand(std::string s);
        debug_command parseCommand(std::string str);
        CPU cpu;
        SDLHandlerDebug sdlhandler;
        static std::map<std::string,debug_command_enum> command_map;
        static std::map<debug_command_enum,void(Debugger::*)(std::vector<std::string> args)> command_fp_map;
        std::set<uint32_t> breakpoints;
    private:
};


#endif // DEBUGGER_H
