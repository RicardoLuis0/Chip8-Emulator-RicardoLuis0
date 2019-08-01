#include "Debugger.h"
#include <curses.h>

std::map<std::string,std::string> Debugger::command_help_map{
    {"exit"," - exit program"},
    {"help"," - list available commands"},
    {"load"," - load rom"},
    {"start"," - start/resume execution"},
    {"stop"," - stop/pause execution"},
    {"step"," - step execution"},
    {"clear"," - clear terminal"},
    {"exec_sp"," - execute special commands"},
    {"break"," - Handle Breakpoints"},
    {"peek"," - print memory/register values"},
};

void Debugger::command_help(std::vector<std::string> args){
    if(args.size()>1&&args[1]=="help"){
        printw("Command: help%s\n",command_help_map["help"].c_str());
        printw("\nUsage:");
        printw("\n  'help'\n  - List commands\n");
        printw("\n  'help [command]'\n  - Display command usage\n");
        return;
    }
    if(args.size()==1){
        printw("Use 'help [command]' for usage information\n\nCommands:\n\n");
        for(auto pair:command_map){
            printw("%s\t%s\n",pair.first.c_str(),command_help_map[pair.first.c_str()].c_str());
        }
    }else{
        if(command_map.find(args[1])!=command_map.end()){
            (this->*command_fp_map[command_map[args[1]]])(args);
        }else{
            printw("Command '%s' does not exist\n",args[1].c_str());
        }
    }
}
