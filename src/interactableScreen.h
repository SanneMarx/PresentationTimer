#ifndef _INTERACTABLE_SCREEN_H_
#define _INTERACTABLE_SCREEN_H_

#include "displayInterface.h"

class InteractableScreen{
public:
    InteractableScreen(Display* display_pointer);
    virtual void handleBecameActive();
    virtual void handlePlayPauze();
    virtual void handleReset();
    virtual void update();
protected:
    Display* display;
};

#endif