#include "Debugger.h"
#include <curses.h>

void Debugger::command_step(std::vector<std::string> args){
    if(running){
        printw("Can't Step Running Emulator\n");
    }else{
        unsigned long steps=1;
        if(args.size()>=2){
            try{
                steps=std::stoul(args[1]);
            }catch(...){
                printw("Invalid argument for step number_of_steps\n");
                return;
            }
        }
        printw("Running %lu Cycles\n",steps);
        while(steps-->0)cpu.doCycle();
        sdlhandler.update(cpu);
    }
}
