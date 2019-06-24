#include "CPU.h"
#include <stdexcept>
#include <cstring>

#define VRAMPOS(x,y) ((y)*64+(x))

#define GETBIT(v,b) ((v>>b)&0x1)

void CPU::clear_screen(){//clear screen
    memset(VRAM,0,sizeof(VRAM));
}

void CPU::draw_sprite(uint8_t X,uint8_t Y,uint8_t height){//draw sprite stored in memory location I at (V[X],V[Y]) coords, with given height
    uint8_t xpos=V[X];
    uint8_t ypos=V[Y];
    VF=0x0;
    for(int i=0;i<height;i++){
        for(int j=0;j<8;j++){
            if(GETBIT(RAM[I+i],j)){
                size_t pos=VRAMPOS(xpos+j,ypos+i);
                VRAM[pos]^=1;
                if(!VRAM[pos]){
                    VF=0x1;
                }
            }
        }
    }
}
