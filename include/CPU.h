#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include "RawInstruction.h"

enum operation_t{
    INVALID_OPERATION,
    SYS,
    CLS,
    RET,
    JMP,
    JMP_V0,
    CALL,
    SE,
    SE_REG,
    SNE,
    SNE_REG,
    MOV,
    MOV_REG,
    MOV_I,
    MOV_V_DT,
    MOV_DT,
    MOV_ST,
    ADD,
    ADD_REG,
    OR,
    AND,
    XOR,
    SUB,
    SHR,
    RSB,
    SHL,
    RND,
    DRW,
    SKP,
    SNKP,
    KEY,
    FONT,
    BCD,
    STR,
    LDR,
};

class CPU {
    public:
        CPU();
        void nextInstruction();
    protected:
        operation_t decodeInstruction(RawInstruction operation);
        void runInstruction(operation_t op,RawInstruction data);
        //operations
        void syscall(uint16_t address);//call system procedure at address
        void cls();//clear screen
        void ret();//return from procedure
        void jump(uint16_t address);//jump to address
        void call(uint16_t address);//call procedure at address
        void skip_if_eq(RawInstruction data);//skip if 
        void skip_if_not_eq(RawInstruction data);
        void skip_if_eq_reg(RawInstruction data);
        //data
        uint16_t font_addr[16]={0};
        uint8_t RAM[4096]={0};//program memory
        uint8_t VRAM[2048]={0};//video memory
        uint8_t KB[16]={0};//keyboard state
        uint8_t DT=0;//delay timer
        uint8_t ST=0;//sound timer
        uint16_t I=0;//address register
        uint16_t PC=0;//program counter
        uint16_t stack[24]={0};
        uint16_t SP=0;//stack pointer
        union{//data registers
            uint8_t V[16];
            struct{
                uint8_t V0;
                uint8_t V1;
                uint8_t V2;
                uint8_t V3;
                uint8_t V4;
                uint8_t V5;
                uint8_t V6;
                uint8_t V7;
                uint8_t V8;
                uint8_t V9;
                uint8_t VA;
                uint8_t VB;
                uint8_t VC;
                uint8_t VD;
                uint8_t VE;
                uint8_t VF;//carry flag
            };
        };
};

#endif // CPU_H
