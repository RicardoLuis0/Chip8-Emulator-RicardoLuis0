#include "Debugger.h"
#include <curses.h>

void Debugger::command_stop(std::vector<std::string> args){
    if(!running){
        printw("Already Stopped\n");
    }else{
        printw("Pausing Emulation\n");
        running=false;
    }
}
