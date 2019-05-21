#ifndef EMULATOR_H
#define EMULATOR_H

#include <string>
#include "Program.h"

class Emulator {
    public:
        Emulator();
        void resetRAM();
        void resetRegisters(unsigned short program_counter);
        void runCycle();
        void loadProgramFile(std::string file,unsigned short starting_position=0x200);
        void loadProgram(Program program,unsigned short starting_position=0x200);
    protected:
        unsigned char RAM[4096];//program memory
        unsigned char VRAM[2048];//video memory
        unsigned char DT;//delay timer
        unsigned char ST;//sound timer
        unsigned short I;//address register
        unsigned short PC;//program counter
        unsigned short stack[24];
        unsigned short SP;//stack pointer
        union{//data registers
            unsigned char V[16];
            struct{
                unsigned char V0;
                unsigned char V1;
                unsigned char V2;
                unsigned char V3;
                unsigned char V4;
                unsigned char V5;
                unsigned char V6;
                unsigned char V7;
                unsigned char V8;
                unsigned char V9;
                unsigned char VA;
                unsigned char VB;
                unsigned char VC;
                unsigned char VD;
                unsigned char VE;
                unsigned char VF;//carry flag
            };
        };
};

#endif // EMULATOR_H
