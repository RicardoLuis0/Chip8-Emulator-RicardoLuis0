#include "Debugger.h"
#include <curses.h>

void Debugger::command_load(std::vector<std::string> args){
    if(args.size()<2){
        printw("Missing filename argument, usage: load filename\n");
        return;
    }
    try{
        cpu.loadProgram(args[1]);
        printw("'%s' loaded into RAM\n",args[1].c_str());
    }catch(std::runtime_error &e){
        printw("%s\n",e.what());
    }
}
