#include "Debugger.h"
#include <curses.h>

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
