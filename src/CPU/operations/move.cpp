#include "CPU.h"
#include <stdexcept>

void CPU::move(uint8_t X,uint8_t value){//move value to V[X]
    V[X]=value;
}

void CPU::move_reg(uint8_t X,uint8_t Y){//move V[Y] to V[X]
    V[X]=V[Y];
}

void CPU::move_i(uint8_t value){//move value to I
    I=value;
}

void CPU::move_reg_dt(uint8_t X){//move DT to V[X]
    V[X]=DT;
}

void CPU::move_dt(uint8_t X){//move DT to V[X]
    DT=V[X];
}

void CPU::move_st(uint8_t X){//move ST to V[X]
    ST=V[X];
}
