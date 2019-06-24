#include "Debugger.h"
#include <curses.h>

void Debugger::command_start(std::vector<std::string> args){
    if(running){
        printw("Already Running\n");
    }else{
        printw("Resuming Emulation\n");
        running=true;
        justresumed=true;
    }
}
