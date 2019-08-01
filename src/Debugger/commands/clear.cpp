#include "Debugger.h"
#include <curses.h>

void Debugger::command_clear(std::vector<std::string> args){
    if(args[0]=="help"||(args.size()>1&&args[1]=="help")){
        printw("Command: clear%s\n",command_help_map["clear"].c_str());
        printw("\nUsage:");
        printw("\n  'clear'\n  - Clears Terminal\n");
        return;
    }
    clear();
}
