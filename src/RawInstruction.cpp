#include "RawInstruction.h"

RawInstruction::RawInstruction(uint16_t w):whole(w){}
RawInstruction::RawInstruction(uint8_t byte0,uint8_t byte1):section34(byte1),section12(byte0){}
