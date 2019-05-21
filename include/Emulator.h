#ifndef EMULATOR_H
#define EMULATOR_H

#include <string>
#include "Program.h"
#include "RawInstruction.h"

class Emulator {
    public:
        Emulator();
        void runCycle();
        void resetRAM();
        void resetVRAM();
        void resetRegisters(unsigned short program_counter);
        void loadProgramFile(std::string file,unsigned short starting_position=0x200);
        void loadProgram(Program program,unsigned short starting_position=0x200);
    protected:
        void loadFonts(const unsigned char fonts[16][5],unsigned short load_address);
        void doSound();
        RawInstruction readInstruction();
        //data
        unsigned short font_addr[16]={0};
        unsigned char RAM[4096]={0};//program memory
        unsigned char VRAM[2048]={0};//video memory
        unsigned char KB[16]={0};//keyboard state
        unsigned char DT=0;//delay timer
        unsigned char ST=0;//sound timer
        unsigned short I=0;//address register
        unsigned short PC=0;//program counter
        unsigned short stack[24]={0};
        unsigned short SP=0;//stack pointer
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
