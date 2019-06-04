#include "Debugger.h"
#include <stdexcept>
#include <curses.h>

class UnclosedStringException:std::runtime_error{
    public:
        UnclosedStringException():runtime_error("Unclosed String In splitCommand"){}
};

std::vector<std::string> Debugger::splitCommand(std::string s){
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
    if(buffer.length()>0){
        temp.push_back(buffer);
    }
    return temp;
}

Debugger::Debugger(){
    
}

std::map<std::string,debug_command_enum> Debugger::command_map{
    {"exit",CMD_EXIT},
    {"help",CMD_HELP},
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

static void clearline(){
    int y,x;
    getyx(stdscr,y,x);
    move(y,0);
    clrtoeol();
}

static void clearchar(){
    int y,x;
    getyx(stdscr,y,x);
    move(y,x-1);
    clrtoeol();
}

void Debugger::startDebug(){
    //noecho();
    timeout(10);
    printw("Debugging Started\n\n>");
    debug_command cmd;
    std::string buffer;
    CPU cpu;
    while(1){
        //getch with timeout
        char c=getch();
        if(c!=-1){
            //if char is /n, try to parse command, else add char to buffer and print it out
            if(c=='\n'){
                //clearline();
                cmd=parseCommand(buffer);
                buffer="";
                runCommand(cmd);
                printw(">");
            }else if(c=='\b'){
                if(buffer.length()>0){
                    buffer.resize(buffer.length()-1);
                    //clearchar();
                    clrtoeol();
                }
            }else{
                //printw("%c",c);
                buffer+=c;
            }
        }
        sdlhandler.pollEvents(cpu);
    }
}
