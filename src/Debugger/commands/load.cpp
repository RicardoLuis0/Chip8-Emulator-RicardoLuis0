#include "Debugger.h"
#include <curses.h>

void Debugger::command_load(std::vector<std::string> args){
    if(args[0]=="help"||(args.size()>1&&args[1]=="help")){
        printw("Command: %s\n",command_help_map["load"].c_str());
    print_usage:
        printw("\nUsage:");
        printw("\n  'load [filename]'\n  - Load ROM file into RAM\n");
        return;
    invalid_usage:
        printw("Invalid Usage\n");
        goto print_usage;
    }
    if(args.size()<2){
        goto invalid_usage;
    }
    try{
        cpu.loadProgram(args[1]);
        printw("'%s' loaded into RAM\n",args[1].c_str());
    }catch(std::runtime_error &e){
        printw("%s\n",e.what());
    }
}
