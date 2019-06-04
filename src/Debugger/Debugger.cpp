#include "Debugger.h"
#include <curses.h>

Debugger::UnclosedStringException::UnclosedStringException():runtime_error("Unclosed String In splitCommand"){}

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

void Debugger::startDebug(){
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
                cmd=parseCommand(buffer);
                buffer="";
                runCommand(cmd);
                printw(">");
            }else if(c=='\b'){
                if(buffer.length()>0){
                    buffer.resize(buffer.length()-1);
                    clrtoeol();
                }
            }else{
                buffer+=c;
            }
        }
        sdlhandler.pollEvents(cpu);
    }
}
