#include "CPU.h"
#include <stdexcept>

void CPU::read_key(uint8_t X){//wait for keypress, and store it at V[X]
    waiting_for_input=true;
    input_to=X;
}
