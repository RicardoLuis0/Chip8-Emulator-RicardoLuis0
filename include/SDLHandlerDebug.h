#ifndef SDLHANDLERDEBUG_H
#define SDLHANDLERDEBUG_H

#include "SDLHandler.h"

class SDLHandlerDebug : public SDLHandler{
    public:
        using SDLHandler::drawScreen;
        using SDLHandler::pollEvents;
};

#endif // SDLHANDLERDEBUG_H
