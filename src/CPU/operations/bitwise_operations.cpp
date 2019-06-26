#include "CPU.h"
#include <stdexcept>


void CPU::or_operation(uint8_t X,uint8_t Y){//move V[X] | V[Y] to V[X]
    V[X]|=V[Y];
}

void CPU::and_operation(uint8_t X,uint8_t Y){//move V[X] & V[Y] to V[X]
    V[X]&=V[Y];
}

void CPU::xor_operation(uint8_t X,uint8_t Y){//move V[X] ^ V[Y] to V[X]
    V[X]^=V[Y];
}

void CPU::shift_right(uint8_t X,uint8_t Y){//shift V[X] to the right by 1, store least significant bit in VF
    VF=V[X]&1;
    V[X]>>=1;
}

void CPU::shift_left(uint8_t X,uint8_t Y){//shift V[X] to the left by 1, store most significant bit in VF
    VF=(V[X]>>7)&1;
    V[X]<<=1;
}
