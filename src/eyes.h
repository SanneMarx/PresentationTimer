#ifndef _EYES_H_
#define _EYES_H_

#include "Arduino.h"
#include "PxMatrix.h"
#include "icons.h"
#include "colors.h"
#include "interactableScreen.h"

enum EYE_TYPE {CIRCLE, HEART};

class Eyes: public InteractableScreen
{
public:
    Eyes(PxMATRIX* display_pointer);

    virtual void handleBecameActive();
    virtual void handlePlayPauze();
    virtual void handleReset();
    virtual void update();
private:
    // User preference data
    const unsigned long color_transition_millis = 10000;

    // Class data
    EYE_TYPE eye_type = CIRCLE;
    void drawCircleEyes();
    void drawHeartEyes();
    void setNewTargetColor();
    unsigned long eyes_start_millis = 0;
    uint8_t last_color[3];
    uint8_t next_color[3];
    uint8_t interped_color[3];
};

#endif