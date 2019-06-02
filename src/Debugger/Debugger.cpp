#include "Debugger.h"
#include <thread>
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

void thread_entrypoint(Debugger * data){
    data->run_thread=true;
    data->readCommandThread();
}

void Debugger::readCommandThread(){
    while(run_thread){
        if(!is_command_pending&&run_thread){
            std::lock_guard<std::mutex> lock(command_mutex);
            std::string buffer;
            std::getline(std::cin,buffer);
            last_command=parseCommand(buffer);
            is_command_pending=true;
        }
    }
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
    
    
    
    return {CMD_INVALID,{str,"unknown error parsing command"}};
}

void Debugger::startDebug(){
    std::thread commandReader(thread_entrypoint,this);
    while(1){
        
    }
}
