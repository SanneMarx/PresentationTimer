#ifndef _NYAN_SCREEN_H_
#define _NYAN_SCREEN_H_

#include "Arduino.h"
#include "PxMatrix.h"
#include "icon.h"
#include "colors.h"
#include "interactableScreen.h"
#include "nyan_frames.h"

class NyanScreen: public InteractableScreen{
public:
    NyanScreen(PxMATRIX* display_pointer);
    virtual void handleBecameActive();
    virtual void handlePlayPauze();
    virtual void handleReset();
    virtual void update();
private:
    void drawNyanAnimation();
    void determineActiveFrame();
    bool play_active = true;
    int active_frame_nr = 0;
    const int ticks_between_frame_change = 10;
    int ticks_since_frame_change = 0;
    static const int NUM_FRAMES = 12;
    const unsigned short* nyan_frames[NUM_FRAMES] ={nyan_frame_0, nyan_frame_1, nyan_frame_2, nyan_frame_3,
    nyan_frame_4, nyan_frame_5, nyan_frame_6, nyan_frame_7, nyan_frame_8, nyan_frame_9, nyan_frame_10,
    nyan_frame_11};
};
#endif