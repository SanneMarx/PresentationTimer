#ifndef PRESENTATION_TIMER_TIME_DISPLAYER_H
#define PRESENTATION_TIMER_TIME_DISPLAYER_H


#include <Ticker.h>
#include <PxMatrix.h>
#include <timer_font.h>
#include "colors.h"

class TimeDisplayer{
    public:
        TimeDisplayer(PxMATRIX& matrix_display);

        void start();

        void setVisible(bool visible);

        void setInitialDuration(int duration);
    
    private:
        Ticker time_ticker;
        PxMATRIX display;

        bool draw_colon = true;
        bool is_visible = false;
        int initial_duration = 0;
        int remaining_duration = 0;

        void update();

        void printDoubleDigitNumberAt(int num, int x, int y);

        void drawAndUpdateColonAt(int x, int y);

        void secondsToMinutesAndSeconds(int total_seconds, int& minutes, int& seconds);

        void writeMinutesSeconds(int time_m, int time_s, uint16_t color);

        void visualize();
};

#endif