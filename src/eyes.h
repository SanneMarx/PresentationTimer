#ifndef _EYES_H_
#define _EYES_H_

#include "Arduino.h"
#include "PxMatrix.h"
#include "icon.h"
#include "colors.h"
#include "interactableScreen.h"

enum COLOR_TYPE {BREATHING, RAINBOW};

class Eyes: public InteractableScreen
{
public:
    Eyes(PxMATRIX* display_pointer);

    const Icon* get_new_eye_icon();

    virtual void handleBecameActive();
    virtual void handlePlayPauze();
    virtual void handleReset();
    virtual void update();
private:
    int xy_margin = 3; //hidden pixels at top, left, right of display
    int max_eye_size = 32; // display is 64x32 so max icon size is 32x32

    static const int NUM_EYES = 3;
    const Icon* eye_icons[NUM_EYES] = {&large_heart, &small_circle, &large_um_u};
    int active_eye = 0;
    
    unsigned long color_transition_millis = 10000;
    float transition_ratio = 0.0f;
    COLOR_TYPE color_type = BREATHING;
    const Icon* eye_icon;
    void setNewTargetColor();
    void drawIconEyes();
    unsigned long eyes_start_millis = 0;
    uint8_t last_color[3];
    uint8_t next_color[3];
    uint8_t next_next_color[3];
    uint8_t interped_color[3];
};

#endif