#include "Debugger.h"
#include <iostream>
#include <stdexcept>
#include <map>

class UnclosedStringException:std::runtime_error{
    public:
        UnclosedStringException():runtime_error("Unclosed String In splitCommand"){}
};

static std::vector<std::string> splitCommand(std::string s){
    std::vector<std::string> temp;
    std::string buffer;
    bool reading_string=false;
    bool reading_escape=false;
    for(char c:s){
        if(reading_string){
            if(reading_escape){
                buffer+=c;
                reading_escape=false;
            }else{
                if(c=='\\'){
                    reading_escape=true;
                }else if(c=='"'){
                    temp.push_back(buffer);
                    reading_string=false;
                }
            }
        }else{
            if(c==' '||c=='"'){
                if(buffer.length()>0)temp.push_back(buffer);
                if(c=='"'){
                    reading_string=true;
                    reading_escape=false;
                }
            }else{
                buffer+=c;
            }
        }
    }
    if(reading_string){
        throw UnclosedStringException();
    }
    return temp;
}

Debugger::Debugger(){
    
}

static std::map<std::string,debug_command_enum> command_map{
    {"exit",CMD_EXIT}
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
            return {CMD_INVALID,{str,args[0]+" is not a valid command"}};
        }
    }else{
        return {CMD_INVALID,{str,"command must not be empty"}};
    }
    return {CMD_INVALID,{str,"unknown error parsing command"}};
}

void Debugger::startDebug(){
    debug_command command;
    std::string buffer;
    while(1){
        //getch with timeout
        //if char is /n, try to parse command, else add char to buffer and print it out
        command=parseCommand(buffer);
    }
}
