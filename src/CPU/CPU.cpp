#include "CPU.h"
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
    const uint8_t &_V0,
    const uint8_t &_V1,
    const uint8_t &_V2,
    const uint8_t &_V3,
    const uint8_t &_V4,
    const uint8_t &_V5,
    const uint8_t &_V6,
    const uint8_t &_V7,
    const uint8_t &_V8,
    const uint8_t &_V9,
    const uint8_t &_VA,
    const uint8_t &_VB,
    const uint8_t &_VC,
    const uint8_t &_VD,
    const uint8_t &_VE,
    const uint8_t &_VF
):font_addr(_font_addr),RAM(_RAM),VRAM(_VRAM),KB(_KB),DT(_DT),ST(_ST),I(_I),PC(_PC),stack(_stack),SP(_SP),V0(_V0),V1(_V1),V2(_V2),V3(_V3),V4(_V4),V5(_V5),V6(_V6),V7(_V7),V8(_V8),V9(_V9),VA(_VA),VB(_VB),VC(_VC),VD(_VD),VE(_VE),VF(_VF){}

CPU::CPU(){
    
}
