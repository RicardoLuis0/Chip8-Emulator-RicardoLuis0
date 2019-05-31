#include "CPU.h"

RawInstruction CPU::nextInstruction(){
    uint8_t byte=RAM[PC++];
    return {byte,RAM[PC++]};
}
