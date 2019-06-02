#ifndef SDLHANDLER_H
#define SDLHANDLER_H

#include "CPU.h"

class SDLHandler {
    public:
        SDLHandler();
        bool update(CPU &cpu);
        virtual ~SDLHandler();
    protected:
        void drawScreen(CPU &cpu);
        bool pollEvents(CPU &cpu);
        bool handleEvent(CPU &cpu,union SDL_Event * e);
        struct SDL_Renderer * renderer;
        struct SDL_Window * window;
    private:
};

#endif // SDLHANDLER_H
