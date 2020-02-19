#ifndef _TIME_WRITER_H_
#define _TIME_WRITER_H_

#include <PxMatrix.h>

class TimeWriter
{
public:
    TimeWriter();
    void setDisplayRefence();
    void printDoubleDigitNumberAt(PxMATRIX& display, int num, int x, int y);

private:
};

#endif