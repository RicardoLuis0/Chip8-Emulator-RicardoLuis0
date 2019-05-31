#include "CPU.h"
#include <stdexcept>

void CPU::load_font(uint8_t X){//move the location of the font for V[X] to I
    I=font_addr[V[X]];
}

void CPU::binary_coded_decimal(uint8_t X){//store the binary coded decimal value of V[X] at I,I+1,I+2
    uint8_t t1=V[X]%10;
    uint8_t t2=(V[X]/10)%10;
    uint8_t t3=(V[X]/100)%10;
    RAM[I]=t1;
    RAM[I+1]=t2;
    RAM[I+2]=t3;
}

void CPU::store(uint8_t X){//store the values of V[0]~V[X] to memory starting at I
    for(int i=0;i<=X;i++){
        RAM[I+i]=V[i];
    }
}

void CPU::load(uint8_t X){//load the values of V[0]~V[X] from memory starting at I
    for(int i=0;i<=X;i++){
        V[i]=RAM[I+i];
    }
}
