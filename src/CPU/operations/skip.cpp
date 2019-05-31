#include "CPU.h"
#include <stdexcept>

void CPU::skip_if_eq(uint8_t X,uint8_t value){//skip next instruction if V[X] == value
    if(V[X]==value)PC+=2;
}

void CPU::skip_if_eq_reg(uint8_t X,uint8_t Y){//skip next instruction if V[X] == V[Y]
    if(V[X]==V[Y])PC+=2;
}

void CPU::skip_if_not_eq(uint8_t X,uint8_t value){//skip next instruction if V[X] != value
    if(V[X]!=value)PC+=2;
}

void CPU::skip_if_not_eq_reg(uint8_t X,uint8_t Y){//skip next instruction if V[X] != V[Y]
    if(V[X]!=V[Y])PC+=2;
}

void CPU::skip_key(uint8_t X){//skip next instruction if the key at V[X] is currently pressed
    if(V[X]<16&&KB[V[X]])PC+=2;
}

void CPU::skip_not_key(uint8_t X){//skip next instruction if the key at V[X] is currently NOT pressed
    if(V[X]<16&&!KB[V[X]])PC+=2;
}
