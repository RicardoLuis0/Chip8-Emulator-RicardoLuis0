#include "CPU.h"
#include <stdexcept>

void CPU::skip_if_eq(uint8_t X,uint8_t value){//skip next instruction if V[X] == value
    throw std::runtime_error("Unimplemented Operation");
}

void CPU::skip_if_eq_reg(uint8_t X,uint8_t Y){//skip next instruction if V[X] == V[Y]
    throw std::runtime_error("Unimplemented Operation");
}

void CPU::skip_if_not_eq(uint8_t X,uint8_t value){//skip next instruction if V[X] != value
    throw std::runtime_error("Unimplemented Operation");
}

void CPU::skip_if_not_eq_reg(uint8_t X,uint8_t Y){//skip next instruction if V[X] != V[Y]
    throw std::runtime_error("Unimplemented Operation");
}

void CPU::skip_key(uint8_t X){//skip next instruction if the key at V[X] is currently pressed
    throw std::runtime_error("Unimplemented Operation");
}

void CPU::skip_not_key(uint8_t X){//skip next instruction if the key at V[X] is currently NOT pressed
    throw std::runtime_error("Unimplemented Operation");
}
