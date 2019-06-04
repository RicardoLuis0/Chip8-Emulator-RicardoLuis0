#include "Debugger.h"
#include <curses.h>

std::map<debug_command_enum,void(Debugger::*)(std::vector<std::string> args)> Debugger::command_fp_map{
    {CMD_EXIT,Debugger::command_exit},
    {CMD_HELP,Debugger::command_help},
};

void Debugger::runCommand(debug_command cmd){
    if(cmd.type==CMD_INVALID){
        printw("%s\n",cmd.args[1].c_str());
    }else if(command_fp_map.find(cmd.type)!=command_fp_map.end()){
        (this->*command_fp_map[cmd.type])(cmd.args);
    }else{
        printw("Unknown command type: %x",cmd.type);
    }
}
