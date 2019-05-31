#include "CPU.h"
#include <stdexcept>

void CPU::load_font(uint8_t X){//move the location of the font for V[X] to I
    throw std::runtime_error("Unimplemented Operation");
}

void CPU::binary_coded_decimal(uint8_t X){//store the binary coded decimal value of V[X] at I,I+1,I+2
    throw std::runtime_error("Unimplemented Operation");
}

void CPU::store(uint8_t X){//store the values of V[0]~V[X] to memory starting at I
    throw std::runtime_error("Unimplemented Operation");
}

void CPU::load(uint8_t X){//load the values of V[0]~V[X] from memory starting at I
    throw std::runtime_error("Unimplemented Operation");
}
