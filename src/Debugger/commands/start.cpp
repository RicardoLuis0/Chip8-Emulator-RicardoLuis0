#include "Debugger.h"
#include <curses.h>

void Debugger::command_start(std::vector<std::string> args){
    if(args[0]=="help"||(args.size()>1&&args[1]=="help")){
        printw("Command: start%s\n",command_help_map["start"].c_str());
        printw("\nUsage:");
        printw("\n  'start'\n  - Sgtart/Resume Emulation\n");
        return;
    }
    if(running){
        printw("Already Running\n");
    }else{
        printw("Resuming Emulation\n");
        running=true;
        justresumed=true;
    }
}
