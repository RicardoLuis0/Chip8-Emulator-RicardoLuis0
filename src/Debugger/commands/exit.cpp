#include "Debugger.h"
#include "QuitException.h"
#include <curses.h>

void Debugger::command_exit(std::vector<std::string> args){
    if(args[0]=="help"||(args.size()>1&&args[1]=="help")){
        printw("Command: exit%s\n",command_help_map["exit"].c_str());
        printw("\nUsage:");
        printw("\n  'exit'\n  - Exit Program\n");
        return;
    }
    throw QuitException(0);
}
