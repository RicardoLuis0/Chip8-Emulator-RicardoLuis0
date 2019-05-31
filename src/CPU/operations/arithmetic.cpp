#include "CPU.h"
#include <stdexcept>

void CPU::add(uint8_t X,uint8_t value){//add value to V[X]
    V[X]+=value;
}

void CPU::add_reg(uint8_t X,uint8_t Y){//add V[Y] to V[X]
    VF=(V[X]+V[Y]>0xFF);
    V[X]+=V[Y];
}

void CPU::add_i(uint8_t X){//add V[X] to I
    VF=(I+V[X]>0xFFF);
    I+=V[X];
}

void CPU::subtract(uint8_t X,uint8_t Y){//subtract V[Y] from V[X]
    VF=(V[X]-V[Y]>0);
    V[X]-=V[Y];
}

void CPU::reverse_subtract(uint8_t X,uint8_t Y){//move V[Y]-V[X] to V[X]
    VF=(V[Y]-V[X]>0);
    V[X]=V[Y]-V[X];
}
