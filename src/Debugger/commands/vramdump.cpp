#include "Debugger.h"
#include <curses.h>
#include <fstream>

void Debugger::command_vramdump(std::vector<std::string> args){
    std::ofstream dump("data.vramdump",std::ios::binary);
    if(!dump){
        printw("Could not write to 'data.vramdump'\n");
        return;
    }
    for(uint8_t byte:cpu.VRAM){
        dump<<(byte==0?0x0:0xFF);
    }
    printw("VRAM written to 'data.vramdump'\n");
}
