#include "timer.h"

Timer::Timer(PxMATRIX* display_pointer): InteractableScreen(display_pointer){
} 

void Timer::printDoubleDigitNumberAt(int num, int x, int y)
{
    // The used font has an offset for numbers in the range [10 - 19] of 1 pixel in x direction
    int x_offset = (20 > num && num >= 10) ? 1 : 0;
    display->setCursor(x - x_offset, y);
    if (num < 10)
    {
        display->print("0");
    }
    display->print(num);
}


void Timer::drawAndUpdateColonAt(int x, int y)
{
    display->setCursor(x, y);
    if (draw_colon)
    {
        display->print(":");
    }
    if (flash_colon){
        draw_colon = !draw_colon;
    }
}

void Timer::secondsToMinutesAndSeconds(int total_seconds, int &minutes, int &seconds)
{
    minutes = total_seconds / 60;
    seconds = total_seconds - minutes * 60;
}

void Timer::writeMinutesSeconds(int time_m, int time_s, uint16_t color)
{
    display->setTextColor(color);
    display->setFont(&FreeSansBold12pt7b);

    printDoubleDigitNumberAt(time_m, 2, 25);
    drawAndUpdateColonAt(29, 23);
    printDoubleDigitNumberAt(time_s, 35, 25);
}

void Timer::drawTimeFromSeconds(int input_seconds){
    display->clearDisplay();
    int minutes, seconds;
    int display_time = (input_seconds > 0) ? input_seconds : 0;
    secondsToMinutesAndSeconds(display_time, minutes, seconds);
    uint8_t interp_color[3];
    interpColors(GREEN, RED, float(display_time) / float(presenter_time_limit_s), interp_color);
    if (draw_time) {
        writeMinutesSeconds(minutes, seconds, toColor565(interp_color));
    }
    // Flash the time on/off when time ran out
    if (input_seconds <= 0) {
        draw_time = !draw_time;
    }
}

void Timer::update(){
    switch(clock_state){
        case PAUZE:
            pauzed_update();
            break;
        case RUNNING:
            running_update();
            break;
    }
}

void Timer::pauzed_update(){

}

void Timer::running_update(){
    unsigned int s_timer_on = ((millis() - clock_start_millis) * speed_mult) / 1000;
    int time_to_display = presenter_time_limit_s - s_timer_on;
    if (time_to_display != last_display_seconds){
        last_display_seconds = time_to_display;
        drawTimeFromSeconds(last_display_seconds);
    }
}

void Timer::handleReset(){
    clock_start_millis = millis();
    last_display_seconds = presenter_time_limit_s;
    draw_time = true;
    drawTimeFromSeconds(last_display_seconds);
}

void Timer::handlePlayPauze(){
    switch(clock_state){
        case RUNNING:
            clock_state = PAUZE;
            break;
        case PAUZE:
            // Change the start millis so that when the clock continues running, it has the same time as when it last updated (-750ms so it feels responsive)
            clock_start_millis = millis() - (presenter_time_limit_s - last_display_seconds) * 1000 - 750;
            clock_state = RUNNING;
            break;
        default:
            break;
    }
}

void Timer::handleBecameActive(){
    handleReset();
}