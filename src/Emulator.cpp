#include <cstring>
#include <iostream>

#include "Emulator.h"
#include "FileLoader.h"
template<typename T1,typename T2>
constexpr T1 min(T1 a,T2 b){
    return (a<b?a:b);
}

constexpr unsigned char getMemBit(unsigned char val,unsigned char pos){
    return (val>>pos)&0x1;
}

constexpr unsigned short calcVRAMPos(unsigned char x,unsigned char y){
    return y*64+x;
}

void Emulator::runCycle(){
    if(DT)DT--;
    if(ST){
        doSound();
        ST--;
    }
    bool carry_borrow_temp;
    RawInstruction operation=readInstruction();
    switch(operation.section1){
    case 0x0://NNN=operation.section234
        switch(operation.section234){
        case 0x0E0://Clears the screen
            resetVRAM();
            break;
        case 0x0EE://Returns from a subroutine
            PC=stack[--SP];
            break;
        default://Calls RCA 1802 program at address NNN
            throw std::runtime_error("RCA calls are not supported");
            break;
        }
        break;
    case 0x1://NNN=operation.section234, Jumps to address NNN
        PC=operation.section234;
        //throw std::runtime_error("unimplemented operation");
        break;
    case 0x2://NNN=operation.section234, Calls subroutine at NNN
        stack[SP++]=PC;
        PC=operation.section234;
        break;
    case 0x3://X=operation.section2,NN=operation.section34, Skips the next instruction if VX equals NN
        if(V[operation.section2]==operation.section34){
            readInstruction();
        }
        break;
    case 0x4://X=operation.section2,NN=operation.section34, Skips the next instruction if VX doesn't equal NN
        if(V[operation.section2]==operation.section34){
            readInstruction();
        }
        break;
    case 0x5://X=operation.section2,Y=operation.section3
        switch(operation.section4){
        case 0x0://Skips the next instruction if VX equals VY
            if(V[operation.section2]==V[operation.section3]){
                readInstruction();
            }
            break;
        default:
            throw std::runtime_error("unsupported operation");
        }
        break;
    case 0x6://X=operation.section2,NN=operation.section34, Sets VX to NN
        V[operation.section2]=operation.section34;
        break;
    case 0x7://X=operation.section2,NN=operation.section34, Adds NN to VX
        V[operation.section2]+=operation.section34;
        break;
    case 0x8://X=operation.section2,Y=operation.section3
        switch(operation.section4){
        case 0x0://Sets VX to the value of VY
            V[operation.section2]=V[operation.section3];
            break;
        case 0x1://Sets VX to VX|VY (BITWISE OR)
            V[operation.section2]|=V[operation.section3];
            break;
        case 0x2://Sets VX to VX&VY (BITWISE AND)
            V[operation.section2]&=V[operation.section3];
            break;
        case 0x3://Sets VX to VX^VY (BITWISE XOR)
            V[operation.section2]^=V[operation.section3];
            break;
        case 0x4://Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't
            carry_borrow_temp=(int(V[operation.section2])+V[operation.section3]>255);
            V[operation.section2]+=V[operation.section3];
            VF=carry_borrow_temp;
            break;
        case 0x5://VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't
            carry_borrow_temp=(int(V[operation.section2])-V[operation.section3]<0);
            V[operation.section2]-=V[operation.section3];
            VF=carry_borrow_temp;
            break;
        case 0x6://Stores the least significant bit of VX in VF and then shifts VX to the right by 1
            carry_borrow_temp=V[operation.section2]&1;
            V[operation.section2]>>=1;
            VF=carry_borrow_temp;
            break;
        case 0x7://Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't
            carry_borrow_temp=(int(V[operation.section3])-V[operation.section2]<0);
            V[operation.section3]-=V[operation.section2];
            VF=carry_borrow_temp;
            break;
        case 0xE://Stores the most significant bit of VX in VF and then shifts VX to the left by 1
            carry_borrow_temp=V[operation.section2]<<7;
            V[operation.section2]<<=1;
            VF=carry_borrow_temp;
            break;
        default:
            throw std::runtime_error("unsupported operation");
        }
        break;
    case 0x9://X=operation.section2,Y=operation.section3
        switch(operation.section4){
        case 0x0://Skips the next instruction if VX doesn't equal VY
            if(V[operation.section2]!=V[operation.section3]){
                readInstruction();
            }
            break;
        default:
            throw std::runtime_error("unsupported operation");
        }
        break;
    case 0xA://NNN=operation.section234, Sets I to address NNN
        I=operation.section234;
        break;
    case 0xB://NNN=operation.section234, Jumps to the address NNN plus V0
        PC=operation.section234+V0;
        break;
    case 0xC://X=operation.section2,NN=operation.section34, Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN
        V[operation.section2]=rand()&operation.section34;
        break;
    case 0xD://X=operation.section2,Y=operation.section3,N=operation.section4, Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels. Each row of 8 pixels is read as bit-coded starting from memory location I; I value doesn't change after the execution of this instruction. As described above, VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that doesn't happen
        throw std::runtime_error("unimplemented operation: DRAW");//TODO
        VF=0x0;
        for(int i=0;i<operation.section4;i++){
            unsigned char data=RAM[I+i];
            for(int j=0;j<8;j++){
                unsigned char bit=getMemBit(data,j);
                if(bit){
                    unsigned short vrpos=calcVRAMPos(operation.section2+j,operation.section3+i);
                    if(!(VRAM[vrpos]=!VRAM[vrpos])){
                        VF=0x1;
                    }
                }
            }
        }
        break;
    case 0xE://X=operation.section2
        switch(operation.section34){
        case 0x9E://Skips the next instruction if the key stored in VX is pressed
            if(KB[V[operation.section2]]){
                readInstruction();
            }
            break;
        case 0xA1://Skips the next instruction if the key stored in VX isn't pressed
            if(!KB[V[operation.section2]]){
                readInstruction();
            }
            break;
        default:
            throw std::runtime_error("unsupported operation");
        }
        break;
    case 0xF://X=operation.section2
        switch(operation.high_byte){
        case 0x07://Set VX to the value of the delay timer
            V[operation.section2]=DT;
            break;
        case 0x0A://A key press is awaited, and then stored in VX. Blocking Operation
            throw std::runtime_error("unimplemented operation: Blocking Key Press");//TODO
            break;
        case 0x15://Sets the delay timer to VX
            DT=V[operation.section2];
            break;
        case 0x18://Sets the sound timer to VX
            ST=V[operation.section2];
            break;
        case 0x1E://Adds VX to I
            I+=V[operation.section2];
            break;
        case 0x29://Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font
            I=font_addr[V[operation.section2]];
            break;
        case 0x33://Stores the binary-coded decimal representation of VX, with the most significant of three digits at the address in I, the middle digit at I+and the least significant digit at I+2
            throw std::runtime_error("unimplemented operation: Binary Coded Decimal");//TODO
            break;
        case 0x55://Stores V0 to VX (including VX) in memory starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified
            for(int i=0;i<operation.section2;i++){
                RAM[i+I]=V[i];
            }
            break;
        case 0x65://Fills V0 to VX (including VX) with values from memory starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified
            for(int i=0;i<operation.section2;i++){
                V[i]=RAM[i+I];
            }
            break;
        default:
            throw std::runtime_error("unsupported operation");
        }
    }
}

Emulator::Emulator(){
    resetRAM();
}

void Emulator::resetRegisters(unsigned short program_counter){
    memset(V,0,sizeof(V));
    memset(stack,0,sizeof(stack));
    SP=0;
    PC=program_counter;
    DT=0;
    ST=0;
    I=0;
}

const unsigned char fontset[16][5]{
    {
        0b01100000,
        0b10010000,
        0b10010000,
        0b10010000,
        0b01100000,
    },//0
    {
        0b00100000,
        0b01100000,
        0b00100000,
        0b00100000,
        0b01110000,
    },//1
    {
        0b11110000,
        0b00010000,
        0b11110000,
        0b10000000,
        0b11110000,
    },//2
    {
        0b11110000,
        0b00010000,
        0b11110000,
        0b00010000,
        0b11110000,
    },//3
    {
        0b10010000,
        0b10010000,
        0b11110000,
        0b00010000,
        0b00010000,
    },//4
    {
        0b11110000,
        0b10000000,
        0b11110000,
        0b00010000,
        0b11100000,
    },//5
    {
        0b01110000,
        0b10000000,
        0b11110000,
        0b10010000,
        0b01100000,
    },//6
    {
        0b11110000,
        0b00010000,
        0b00100000,
        0b01000000,
        0b01000000,
    },//7
    {
        0b01100000,
        0b10010000,
        0b11110000,
        0b10010000,
        0b01100000,
    },//8
    {
        0b01110000,
        0b10010000,
        0b01110000,
        0b00010000,
        0b01100000,
    },//9
    {
        0b01100000,
        0b10010000,
        0b11110000,
        0b10010000,
        0b10010000,
    },//A
    {
        0b11100000,
        0b10010000,
        0b11110000,
        0b10010000,
        0b11100000,
    },//B
    {
        0b01100000,
        0b10010000,
        0b10000000,
        0b10010000,
        0b01100000,
    },//C
    {
        0b11100000,
        0b10010000,
        0b00010000,
        0b10010000,
        0b11100000,
    },//D
    {
        0b11110000,
        0b10000000,
        0b11100000,
        0b10000000,
        0b11110000,
    },//E
    {
        0b11110000,
        0b10000000,
        0b11100000,
        0b10000000,
        0b10000000,
    },//F
};

void Emulator::resetRAM(){
    memset(RAM,0,sizeof(RAM));
    loadFonts(fontset,0x0);
}

void Emulator::resetVRAM(){
    memset(VRAM,0,sizeof(VRAM));
}

void Emulator::loadProgramFile(std::string file,unsigned short starting_position){
    Program program=FileLoader::load(file,4096-starting_position);
    loadProgram(program,starting_position);
    delete program.data;
}

void Emulator::loadProgram(Program program,unsigned short starting_position){
    memcpy(RAM+starting_position,program.data,min(program.length,4096-starting_position));
    resetRegisters(starting_position);
}

RawInstruction Emulator::readInstruction(){
    unsigned char byte=RAM[PC++];
    return {byte,RAM[PC++]};
}

void Emulator::doSound(){
    std::cout<<"Beep!";
    //TODO
}

void Emulator::loadFonts(const unsigned char fonts[16][5],unsigned short load_address=0x0){
    for(int i=0;i<16;i++,load_address+=5){
        font_addr[i]=load_address;
        for(int j=0;j<5;j++){
            RAM[load_address+j]=fonts[i][j];
        }
    }
}
