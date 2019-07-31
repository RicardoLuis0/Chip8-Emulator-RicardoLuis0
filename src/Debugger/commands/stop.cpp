#include "Debugger.h"
#include <curses.h>

void Debugger::command_stop(std::vector<std::string> args){
    if(args[0]=="help"||(args.size()>1&&args[1]=="help")){
        printw("Command: %s\n",command_help_map["stop"].c_str());
        printw("\nUsage:");
        printw("\n  'stop'\n  - Stop/Pause Emulation\n");
        return;
    }
    if(!running){
        printw("Already Stopped\n");
    }else{
        printw("Pausing Emulation\n");
        running=false;
    }
}
