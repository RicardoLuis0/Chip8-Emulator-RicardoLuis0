#include "Debugger.h"
#include <curses.h>

void Debugger::command_exec_sp(std::vector<std::string> args){
    if(args[0]=="help"||(args.size()>1&&args[1]=="help")){
        printw("Command: %s\n",command_help_map["exec_sp"].c_str());
    print_usage:
        printw("\nUsage:");
        printw("\n  'exec_sp clear_screen'\n  - Clear program VRAM\n");
        return;
    invalid_usage:
        printw("Invalid Usage\n");
        goto print_usage;
    }
    if(args.size()<2){
        goto invalid_usage;
    }else if(args[1]=="clear_screen"){
        cpu.clear_screen();
    }else{
        goto invalid_usage;
    }
}
