#include "CPU.h"
#include <stdexcept>

void CPU::add(uint8_t X,uint8_t value){//add value to V[X]
    throw std::runtime_error("Unimplemented Operation");
}

void CPU::add_reg(uint8_t X,uint8_t Y){//add V[Y] to V[X]
    throw std::runtime_error("Unimplemented Operation");
}

void CPU::add_i(uint8_t X){//add V[X] to I
    throw std::runtime_error("Unimplemented Operation");
}

void CPU::subtract(uint8_t X,uint8_t Y){//subtract V[Y] from V[X]
    throw std::runtime_error("Unimplemented Operation");
}

void CPU::reverse_subtract(uint8_t X,uint8_t Y){//move V[Y]-V[X] to V[X]
    throw std::runtime_error("Unimplemented Operation");
}
