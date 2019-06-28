#include "SDLHandler.h"

#include <SDL2/SDL.h>

#define VRAMPOS(x,y) ((y)*64+(x))

SDLHandler::SDLHandler(){
    SDL_CreateWindowAndRenderer(640,320,0,&window,&renderer);
    SDL_RenderPresent(renderer);
}

SDLHandler::~SDLHandler(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

bool SDLHandler::update(CPU &cpu){
    drawScreen(cpu);
    return pollEvents(cpu);
}

void SDLHandler::drawScreen(CPU &cpu){
    std::array<uint8_t,2048> data = cpu.getVRAMData();
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    SDL_Rect rect {x:0,y:0,w:10,h:10};
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    for(int y=0;y<32;y++){
        for(int x=0;x<64;x++){
            if(data[VRAMPOS(x,y)]!=0){
                rect.x=x*10;
                rect.y=y*10;
                SDL_RenderFillRect(renderer,&rect);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

bool SDLHandler::pollEvents(CPU &cpu){
    bool doQuit=false;
    for(SDL_Event e;SDL_PollEvent(&e);){
        if(handleEvent(cpu,&e)){
            doQuit=true;
        }
    }
    return doQuit;
}

int32_t SDLHandler::get_key_num(int32_t sym){
    switch(sym){
    case SDLK_1:
        return 0;
    case SDLK_2:
        return 1;
    case SDLK_3:
        return 2;
    case SDLK_4:
        return 3;
    case SDLK_q:
        return 4;
    case SDLK_w:
        return 5;
    case SDLK_e:
        return 6;
    case SDLK_r:
        return 7;
    case SDLK_a:
        return 8;
    case SDLK_s:
        return 9;
    case SDLK_d:
        return 10;
    case SDLK_f:
        return 11;
    case SDLK_z:
        return 12;
    case SDLK_x:
        return 13;
    case SDLK_c:
        return 14;
    case SDLK_v:
        return 15;
    default:
        return -1;
    }
}

void SDLHandler::handleKey(CPU &cpu,SDL_Keycode sym,bool keyup){
    int key=get_key_num(sym);
    if(key==-1)return;
    if(keyup){
        cpu.keyReleased(key);
    }else{
        cpu.keyPressed(key);
    }
}

bool SDLHandler::handleEvent(CPU &cpu,union SDL_Event * e){
    switch(e->type){
    case SDL_QUIT:
        return true;
    case SDL_KEYDOWN:
        handleKey(cpu,e->key.keysym.sym,false);
        break;
    case SDL_KEYUP:
        handleKey(cpu,e->key.keysym.sym,true);
        break;
    default:
        break;
    }
    return false;
}
