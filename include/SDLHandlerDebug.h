#ifndef SDLHANDLERDEBUG_H
#define SDLHANDLERDEBUG_H

#include "SDLHandler.h"

class SDLHandlerDebug : SDLHandler{
    public:
        using SDLHandler::drawScreen;
        using SDLHandler::pollEvents;
};

#endif // SDLHANDLERDEBUG_H
