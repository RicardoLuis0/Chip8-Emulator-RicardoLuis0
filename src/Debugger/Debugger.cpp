#include "Debugger.h"
#include <curses.h>

Debugger::Debugger(){
    
}

uint32_t Debugger::read_num(std::string s){
    return (s.substr(0,2)=="0x")?stoul(s.substr(2),nullptr,16):stoul(s);
}

void Debugger::startDebug(){
    timeout(10);
    printw("\nDebugging Terminal Started, type 'help' for available commands\n\n>");
    debug_command cmd;
    std::string buffer;
    cpu.clearRAM();
    cpu.clearVRAM();
    cpu.clearRegisters();
    running=false;
    justresumed=false;
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
                }else{
                    printw(">");
                }
            }else{
                buffer+=c;
            }
        }
        //check breakpoint
        if(running&&!justresumed&&breakpoints.count(cpu.PC)>0){
            int tx,ty;
            getyx(stdscr,ty,tx);
            move(ty,0);
            clrtoeol();
            mvprintw(ty,0,"breakpoint @0x%03lx (%lu) triggered, pausing execution.\n>%s",cpu.PC,cpu.PC,buffer.c_str());
            running=false;
        }
        if(running){
            sdlhandler.update(cpu);
            cpu.doCycle();
        }else{
            sdlhandler.pollEvents(cpu);
        }
        justresumed=false;
    }
}
