#include "SDLHandler.h"

#include "SDL2/SDL.h"

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

bool SDLHandler::handleEvent(CPU &cpu,union SDL_Event * e){
    switch(e->type){
    case SDL_QUIT:
        return true;
    default:
        break;
    }
    return false;
}
