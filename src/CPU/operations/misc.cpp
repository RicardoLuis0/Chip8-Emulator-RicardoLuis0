#include "CPU.h"
#include <stdexcept>

void CPU::sys_call(uint16_t address){//call system procedure at address
    return;//Do nothing on this
}

void CPU::random(uint8_t X,uint8_t mask){//move random number & mask to V[X]
    V[X]=rand()&mask;
}
