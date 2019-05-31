#include "CPU.h"

void CPU::doCycle(){
    if(waiting_for_input)return;
    RawInstruction d=nextInstruction();
    runInstruction(decodeInstruction(d),d);
}
