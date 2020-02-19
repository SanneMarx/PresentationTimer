#include "time_writer.h"

TimeWriter::TimeWriter(){
} 

void TimeWriter::setDisplayRefence(){
}

void TimeWriter::printDoubleDigitNumberAt(PxMATRIX& display, int num, int x, int y)
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