#include "CPU.h"
#include <stdexcept>

void CPU::jump(uint16_t address){//jump to address
    PC=address;
}

void CPU::jump_v0(uint16_t address){//jump to V[0]+address
    PC=V0+address;
}

void CPU::call_procedure(uint16_t address){//call procedure at address
    stack[SP++]=PC;
    PC=address;
}

void CPU::return_procedure(){//return from procedure
    PC=stack[--SP];
}
