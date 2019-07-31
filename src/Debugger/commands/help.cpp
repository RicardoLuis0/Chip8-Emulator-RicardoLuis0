#include "Debugger.h"
#include <curses.h>

std::map<std::string,std::string> Debugger::command_help_map{
    {"exit","exit\t - exit program"},
    {"help","help\t - show help"},
    {"load","load\t - load rom"},
    {"start","start\t - start/resume execution"},
    {"stop","stop\t - stop/pause execution"},
    {"step","step\t - step execution"},
    {"clear","clear\t - clear terminal"},
    {"exec_sp","exec_sp\t - execute special commands"},
    {"break","break\t - Handle Breakpoints"},
    {"peek","peek\t - print memory/register values"},
};

void Debugger::command_help(std::vector<std::string> args){
    if(args.size()==1){
        printw("Use 'help [command]' for usage information\n\nCommands:\n\n");
        for(auto pair:command_map){
            printw("%s\n",command_help_map[pair.first.c_str()].c_str());
        }
    }else{
        if(command_map.find(args[1])!=command_map.end()){
            (this->*command_fp_map[command_map[args[1]]])(args);
        }else{
            printw("Command '%s' does not exist\n",args[1].c_str());
        }
    }
}
