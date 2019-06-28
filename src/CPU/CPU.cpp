#include "CPU.h"
#include "FileLoader.h"

#include <algorithm>
#include <cstring>

#include <curses.h>

std::array<uint8_t,2048> CPU::getVRAMData(){
    std::array<uint8_t,2048> temp;
    std::copy_n(std::begin(VRAM),2048,temp.begin());
    return temp;
}

void CPU::loadProgram(std::string filepath){
    clearRAM();
    clearVRAM();
    clearRegisters();
    Program program=FileLoader::load(filepath,3584);
    memcpy(RAM+0x200,program.data,(program.length>3584)?3584:program.length);
    delete program.data;
}

void CPU::clearRAM(){
    memset(RAM,0,sizeof(RAM));
    loadFonts(fontset,0x0);
}

void CPU::clearVRAM(){
    memset(VRAM,0,sizeof(VRAM));
}

void CPU::clearRegisters(){
    memset(V,0,sizeof(V));
    memset(stack,0,sizeof(stack));
    SP=0;
    PC=0x200;
    DT=0;
    ST=0;
    I=0;
}

void CPU::keyPressed(uint8_t key){
    if(key>15)return;
    KB[key]=1;
    if(waiting_for_input){
        waiting_for_input=false;
        V[input_to]=key;
    }
}

void CPU::keyReleased(uint8_t key){
    if(key>15)return;
    KB[key]=0;
}

bool CPU::makeSound(){
    return ST>0;
}
