#include "CPU.h"
#include <stdexcept>

void CPU::jump(uint16_t address){//jump to address
    throw std::runtime_error("Unimplemented Operation");
}

void CPU::jump_v0(uint16_t address){//jump to V[0]+address
    throw std::runtime_error("Unimplemented Operation");
}

void CPU::call_procedure(uint16_t address){//call procedure at address
    throw std::runtime_error("Unimplemented Operation");
}

void CPU::return_procedure(){//return from procedure
    throw std::runtime_error("Unimplemented Operation");
}
