#include "Debugger.h"
#include "QuitException.h"

void Debugger::exitDebug(){
    throw QuitException(0);
}
