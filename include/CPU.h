#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <array>
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
    SKP,
    SNKP,
    KEY,
    MOV,
    MOV_REG,
    MOV_I,
    MOV_REG_DT,
    MOV_DT,
    MOV_ST,
    ADD,
    ADD_REG,
    ADD_I,
    SUB,
    RSB,
    OR,
    AND,
    XOR,
    SHR,
    SHL,
    RND,
    DRW,
    LDFNT,
    BCD,
    STR,
    LDR,
};

class CPU {
    public:
        bool makeSound();//if it needs to make a sound
        void keyPressed(uint8_t key);
        void keyReleased(uint8_t key);
        void doCycle();
        std::array<uint8_t,2048> getVRAMData();//for window drawer
        static operation_t decodeInstruction(RawInstruction operation);
        void loadProgram(std::string filepath);
        friend class Debugger;
    protected:
        void clearRAM();
        void clearVRAM();
        void clearRegisters();
        void loadFonts(const uint8_t fonts[16][5],uint16_t load_address=0x0);
        RawInstruction nextInstruction();
        void runInstruction(operation_t op,RawInstruction data);
        //operations
        void sys_call(uint16_t address);//call system procedure at address
        void clear_screen();//clear screen
        void return_procedure();//return from procedure
        void jump(uint16_t address);//jump to address
        void jump_v0(uint16_t address);//jump to V[0]+address
        void call_procedure(uint16_t address);//call procedure at address
        void skip_if_eq(uint8_t X,uint8_t value);//skip next instruction if V[X] == value
        void skip_if_eq_reg(uint8_t X,uint8_t Y);//skip next instruction if V[X] == V[Y]
        void skip_if_not_eq(uint8_t X,uint8_t value);//skip next instruction if V[X] != value
        void skip_if_not_eq_reg(uint8_t X,uint8_t Y);//skip next instruction if V[X] != V[Y]
        void skip_key(uint8_t X);//skip next instruction if the key at V[X] is currently pressed
        void skip_not_key(uint8_t X);//skip next instruction if the key at V[X] is currently NOT pressed
        void read_key(uint8_t X);//wait for keypress, and store it at V[X]
        void move(uint8_t X,uint8_t value);//move value to V[X]
        void move_reg(uint8_t X,uint8_t Y);//move V[Y] to V[X]
        void move_i(uint16_t value);//move value to I
        void move_reg_dt(uint8_t X);//move DT to V[X]
        void move_dt(uint8_t X);//move DT to V[X]
        void move_st(uint8_t X);//move ST to V[X]
        void add(uint8_t X,uint8_t value);//add value to V[X]
        void add_reg(uint8_t X,uint8_t Y);//add V[Y] to V[X]
        void add_i(uint8_t X);//add V[X] to I
        void subtract(uint8_t X,uint8_t Y);//subtract V[Y] from V[X]
        void reverse_subtract(uint8_t X,uint8_t Y);//move V[Y]-V[X] to V[X]
        void or_operation(uint8_t X,uint8_t Y);//move V[X] | V[Y] to V[X]
        void and_operation(uint8_t X,uint8_t Y);//move V[X] & V[Y] to V[X]
        void xor_operation(uint8_t X,uint8_t Y);//move V[X] ^ V[Y] to V[X]
        void shift_right(uint8_t X,uint8_t Y);//shift V[X] to the right by 1, store least significant bit in V[Y]
        void shift_left(uint8_t X,uint8_t Y);//shift V[X] to the left by 1, store most significant bit in V[Y]
        void random(uint8_t X,uint8_t mask);//move random number & mask to V[X]
        void draw_sprite(uint8_t X,uint8_t Y,uint8_t height);//draw sprite stored in memory location I at (V[X],V[Y]) coords, with given height
        void load_font(uint8_t X);//move the location of the font for V[X] to I
        void binary_coded_decimal(uint8_t X);//store the binary coded decimal value of V[X] at I,I+1,I+2
        void store(uint8_t X);//store the values of V[0]~V[X] to memory starting at I
        void load(uint8_t X);//load the values of V[0]~V[X] from memory starting at I
        //internal
        static const uint8_t fontset[16][5];
        uint16_t font_addr[16]={0};
        bool waiting_for_input=false;
        uint8_t input_to=0;
        //data
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
