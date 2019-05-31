#ifndef SDLHANDLER_H
#define SDLHANDLER_H

#include "CPU.h"

class SDLHandler {
    public:
        SDLHandler();
        void update(CPU &cpu);
        virtual ~SDLHandler();
    protected:
        struct SDL_Renderer * renderer;
        struct SDL_Window * window;

    private:
};

#endif // SDLHANDLER_H
