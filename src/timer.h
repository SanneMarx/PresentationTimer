#ifndef _TIME_WRITER_H_
#define _TIME_WRITER_H_

#include <PxMatrix.h>

class Timer
{
public:
    Timer();
    void setDisplay(PxMATRIX* display);
    void printDoubleDigitNumberAt(int num, int x, int y);

private:
    PxMATRIX* display;
};

#endif