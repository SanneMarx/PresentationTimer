#ifndef _INTERACTABLE_SCREEN_H_
#define _INTERACTABLE_SCREEN_H_
#include "PxMatrix.h"

class InteractableScreen{
public:
    InteractableScreen(PxMATRIX* display_pointer);
    virtual void handleBecameActive();
    virtual void handlePlayPauze();
    virtual void handleReset();
    virtual void update();
protected:
    PxMATRIX* display;
};

#endif