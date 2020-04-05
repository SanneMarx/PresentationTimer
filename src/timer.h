#ifndef _TIME_WRITER_H_
#define _TIME_WRITER_H_

#include <PxMatrix.h>
#include "colors.h"
#include <Fonts/FreeSansBold12pt7b.h>


enum CLOCK_STATE {RUNNING, PAUZE};

class Timer
{
public:
    Timer(PxMATRIX* display_pointer);
    void update();
    void printDoubleDigitNumberAt(int num, int x, int y);
    void resetClock();
    void handlePlayPauzePressed();

private:
    // User Preference:
    const bool flash_colon = false;
    const int presenter_time_limit_s = 9 * 60;
    const unsigned int speed_mult = 1; // 1 for normal speed, >1 for speeding up the countdown for testing

    // Class Data
    PxMATRIX* display;
    CLOCK_STATE clock_state = PAUZE;
    bool draw_colon = true;
    bool draw_time = true;
    unsigned long clock_start_millis = 0;
    int last_display_seconds = 0;

    void running_update();
    void pauzed_update();


    void drawAndUpdateColonAt(int x, int y);
    void secondsToMinutesAndSeconds(int total_seconds, int &minutes, int &seconds);
    void writeMinutesSeconds(int time_m, int time_s, uint16_t color);
    void drawTimeFromSeconds(int input_seconds);


};

#endif