#include "CPU.h"
#include <iostream>

void CPU::doCycle(){
    if(waiting_for_input)return;
    RawInstruction d=nextInstruction();
    runInstruction(decodeInstruction(d),d);
    if(DT>0)DT--;
    if(ST>0){
        std::cout<<"\a";//TODO replace with sdl sound stuff
        ST--;
    }
}
