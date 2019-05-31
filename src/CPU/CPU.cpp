#include "CPU.h"
#include <algorithm>

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

CPU::CPU(){
    
}

std::array<uint8_t,2048> CPU::getVRAMData(){
    std::array<uint8_t,2048> temp;
    std::copy_n(std::begin(VRAM),2048,temp.begin());
    return temp;
}

cpu_state CPU::get_cpu_state(){
    return cpu_state(font_addr,RAM,VRAM,KB,DT,ST,I,PC,stack,SP,V);
}
