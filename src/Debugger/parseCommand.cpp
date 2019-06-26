#include "Debugger.h"

std::map<std::string,debug_command_enum> Debugger::command_map{
    {"exit",CMD_EXIT},
    {"help",CMD_HELP},
    {"load",CMD_LOAD},
    {"start",CMD_START},
    {"stop",CMD_STOP},
    {"step",CMD_STEP},
    {"clear",CMD_CLEAR},
    {"ramdump",CMD_RAMDUMP},
    {"vramdump",CMD_VRAMDUMP},
    {"exec_sp",CMD_EXEC_SP},
    {"break",CMD_BREAK},
    {"read_registers",CMD_READ_REGISTERS},
    {"peek",CMD_PEEK},
};

debug_command Debugger::parseCommand(std::string str){
    std::vector<std::string> args;
    try{
        args=splitCommand(str);
    }catch(UnclosedStringException &e){
        return {CMD_INVALID,{str,"Unclosed quoted string"}};
    }
    if(args.size()>0){
        if(command_map.find(args[0])!=command_map.end()){
            return {command_map[args[0]],args};
        }else{
            return {CMD_INVALID,{str,"'"+str+"' is not a valid command"}};
        }
    }else{
        return {CMD_INVALID,{str,"command must not be empty"}};
    }
    return {CMD_INVALID,{str,"unknown error parsing command"}};
}
