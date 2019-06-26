#include "Debugger.h"
#include "Disassembler.h"
#include <curses.h>


void Debugger::command_peek(std::vector<std::string> args){
    if(args.size()<4){
        printw("missing arguments: rel|pos negative_offset positive_offset\n");
        return;
    }
    uint32_t pos;
    if(args[1]=="rel"){
        pos=cpu.PC;
    }else{
        pos=read_num(args[1]);
        if(pos%2){
            printw("pos must not be odd\n");
            return;
        }
    }
    uint32_t start=pos-read_num(args[2]);
    if(start%2){
        printw("negative offset must not be odd\n");
        return;
    }
    uint32_t end=pos+read_num(args[3]);
    if(end%2){
        printw("positive offset must not be odd\n");
        return;
    }
    for(uint32_t i=start;i<=end;i+=2){
        disassembled_instruction inst=Disassembler::disassembleInstruction(cpu.RAM[i],cpu.RAM[i+1]);
        printw("%s\n",inst.getDisplay2(i).c_str());
    }
}
