#include "Debugger.h"
#include <curses.h>

void Debugger::command_step(std::vector<std::string> args){
    if(args[0]=="help"||(args.size()>1&&args[1]=="help")){
        printw("Command: %s\n",command_help_map["step"].c_str());
    print_usage:
        printw("\nUsage:");
        printw("\n  'step'\n  - Step by 1 Instruction\n");
        printw("\n  'step [count]'\n  - Step by 'count' Instruction\n");
        return;
    invalid_usage:
        printw("Invalid Usage\n");
        goto print_usage;
    }
    if(running){
        printw("Can't Step Running Emulator\n");
    }else{
        unsigned long steps=1;
        if(args.size()>1){
            try{
                steps=read_num(args[1]);
            }catch(...){
                goto invalid_usage;
            }
        }
        printw("Running %lu Cycles\n",steps);
        while(steps-->0)cpu.doCycle();
        sdlhandler.update(cpu);
    }
}
