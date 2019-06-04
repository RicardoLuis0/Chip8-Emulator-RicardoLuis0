#include "Debugger.h"
#include <curses.h>

std::map<debug_command_enum,void(Debugger::*)(std::vector<std::string> args)> Debugger::command_fp_map{
    {CMD_EXIT,Debugger::command_exit},
    {CMD_HELP,Debugger::command_help},
    {CMD_LOAD,Debugger::command_load},
    {CMD_START,Debugger::command_start},
    {CMD_STOP,Debugger::command_stop},
    {CMD_STEP,Debugger::command_step},
    {CMD_CLEAR,Debugger::command_clear},
};

void Debugger::runCommand(debug_command cmd){
    if(cmd.type==CMD_INVALID){
        printw("%s\n",cmd.args[1].c_str());
    }else if(command_fp_map.find(cmd.type)!=command_fp_map.end()){
        (this->*command_fp_map[cmd.type])(cmd.args);
    }else{
        printw("Unknown command type: %x\n",cmd.type);
    }
}
