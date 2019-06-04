#include "Debugger.h"
#include <curses.h>

void Debugger::command_clear(std::vector<std::string> args){
    clear();
}
