#include "Debugger.h"
#include <curses.h>

void Debugger::command_read_registers(std::vector<std::string> args){
    printw("PC:0x%03X\n",cpu.PC);
    printw("SP:0x%03X\n",cpu.SP);
    printw("DT:0x%03X\n",cpu.DT);
    printw("ST:0x%03X\n",cpu.ST);
    printw("I:0x%03X\n",cpu.I);
    for(uint8_t i=0;i<16;i++){
        printw("V%X:0x%03X,  KB_%X:%u%s",i,cpu.V[i],i,cpu.KB[i],((i+1)%2?";   ":";\n"));
    }
}
