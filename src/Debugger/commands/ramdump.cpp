#include "Debugger.h"
#include <curses.h>
#include <fstream>

void Debugger::command_ramdump(std::vector<std::string> args){
    std::ofstream dump("data.ramdump",std::ios::binary);
    if(!dump){
        printw("Could not write to 'data.ramdump'\n");
        return;
    }
    for(uint8_t byte:cpu.RAM){
        dump<<byte;
    }
    printw("RAM written to 'data.ramdump'\n");
}
