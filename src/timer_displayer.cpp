#include "time_displayer.h"

TimeDisplayer::TimeDisplayer(PxMATRIX &matrix_display) : display(matrix_display) {}

void TimeDisplayer::start()
{
    remaining_duration = initial_duration;
    time_ticker.attach(1.0f, std::bind(&TimeDisplayer::update, this));
}

void TimeDisplayer::setVisible(bool visible)
{
    is_visible = visible;
}

void TimeDisplayer::setInitialDuration(int duration)
{
    initial_duration = duration;
}

void TimeDisplayer::update()
{
    Serial.println("updating display");
    if (remaining_duration > 0)
    {
        remaining_duration -= 1;
    }
    else
    {
        remaining_duration = remaining_duration;
    }
    if (!is_visible)
    {
        return;
    }
    visualize();
}

void TimeDisplayer::visualize()
{
    Serial.println("writing time");
    display.clearDisplay();
    int minutes, seconds;
    secondsToMinutesAndSeconds(remaining_duration, minutes, seconds);
    uint8_t interp_color[3];
    interp_colors(GREEN, RED, float(remaining_duration) / float(initial_duration), interp_color);
    writeMinutesSeconds(minutes, seconds, to_color565(interp_color));
}

void TimeDisplayer::printDoubleDigitNumberAt(int num, int x, int y)
{
    // The used font has an offset for numbers in the range [10 - 19] of 1 pixel in x direction
    int x_offset = (20 > num && num >= 10) ? 1 : 0;
    display.setCursor(x - x_offset, y);
    if (num < 10)
    {
        display.print("0");
    }
    display.print(num);
}

void TimeDisplayer::drawAndUpdateColonAt(int x, int y)
{
    display.setCursor(x, y);
    if (draw_colon)
    {
        display.print(":");
    }
    draw_colon = !draw_colon;
}

void TimeDisplayer::secondsToMinutesAndSeconds(int total_seconds, int &minutes, int &seconds)
{
    minutes = total_seconds / 60;
    seconds = total_seconds - minutes * 60;
}

void TimeDisplayer::writeMinutesSeconds(int time_m, int time_s, uint16_t color)
{
    return;
    printDoubleDigitNumberAt(time_m, 1, 23);
    drawAndUpdateColonAt(29, 21);
    printDoubleDigitNumberAt(time_s, 36, 23);
}