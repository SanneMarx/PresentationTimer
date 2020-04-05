#include "timer.h"

Timer::Timer(){
} 

void Timer::setDisplay(PxMATRIX* display_pointer){
    display = display_pointer;
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