#ifndef _TIME_WRITER_H_
#define _TIME_WRITER_H_

#include <PxMatrix.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include "interactableScreen.h"
#include "colors.h"

enum CLOCK_STATE {RUNNING, PAUZE};

class Timer: public InteractableScreen
{
public:
    Timer(PxMATRIX* display_pointer);

    void handleBecameActive();
    void handlePlayPauze();
    void handleReset();
    void update();

private:
    // User Preference:
    const bool flash_colon = false;
    const int presenter_time_limit_s = 9 * 60;
    const unsigned int speed_mult = 1; // 1 for normal speed, >1 for speeding up the countdown for testing

    // Class Data
    CLOCK_STATE clock_state = PAUZE;
    bool draw_colon = true;
    bool draw_time = true;
    unsigned long clock_start_millis = 0;
    int last_display_seconds = 0;

    void running_update();
    void pauzed_update();


    void printDoubleDigitNumberAt(int num, int x, int y);
    void drawAndUpdateColonAt(int x, int y);
    void secondsToMinutesAndSeconds(int total_seconds, int &minutes, int &seconds);
    void writeMinutesSeconds(int time_m, int time_s, uint16_t color);
    void drawTimeFromSeconds(int input_seconds);


};

#endif