#include "CPU.h"
#include "FileLoader.h"

#include <algorithm>
#include <cstring>

cpu_state::cpu_state(
    const uint16_t (&_font_addr)[16],
    const uint8_t (&_RAM)[4096],
    const uint8_t (&_VRAM)[2048],
    const uint8_t (&_KB)[16],
    const uint8_t &_DT,
    const uint8_t &_ST,
    const uint16_t &_I,
    const uint16_t &_PC,
    const uint16_t (&_stack)[24],
    const uint16_t &_SP,
    const uint8_t (&_V)[16]
):font_addr(_font_addr),RAM(_RAM),VRAM(_VRAM),KB(_KB),DT(_DT),ST(_ST),I(_I),PC(_PC),stack(_stack),SP(_SP),V(_V){}

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

cpu_state CPU::get_cpu_state(){
    return cpu_state(font_addr,RAM,VRAM,KB,DT,ST,I,PC,stack,SP,V);
}
