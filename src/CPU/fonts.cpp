#include "CPU.h"

const uint8_t CPU::fontset[16][5]{
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

void CPU::loadFonts(const unsigned char fonts[16][5],unsigned short load_address){
    for(int i=0;i<16;i++,load_address+=5){
        font_addr[i]=load_address;
        for(int j=0;j<5;j++){
            RAM[load_address+j]=fonts[i][j];
        }
    }
}
