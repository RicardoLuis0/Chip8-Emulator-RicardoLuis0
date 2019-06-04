#include "Debugger.h"
#include "QuitException.h"

void Debugger::command_exit(std::vector<std::string> args){
    throw QuitException(0);
}
