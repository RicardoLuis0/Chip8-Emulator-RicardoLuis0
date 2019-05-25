#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <string>
#include <cstdint>

#include "RawInstruction.h"
struct disassembled_instruction{
    disassembled_instruction(RawInstruction _data);//invalid constructor
    disassembled_instruction(RawInstruction _data,std::string asm_str);//valid constructor
    std::string getDisplay();
    std::string getDisplay(uint16_t location);
    RawInstruction data;
    bool valid;
    std::string asm_str;
};

class Disassembler {
    public:
        static disassembled_instruction disassembleInstruction(uint8_t byte0,uint8_t byte1);
        static disassembled_instruction disassembleInstruction(uint16_t bytewhole);
        static disassembled_instruction disassembleInstruction(RawInstruction instruction);
};

#endif // DISASSEMBLER_H
