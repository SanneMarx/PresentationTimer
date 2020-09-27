#ifndef _LOOPTIMER_H_
#define _LOOPTIMER_H_

#include <Arduino.h>

// Debugging class for benchmarking the loop execution time
class LoopTimer{
public:
    LoopTimer(unsigned int n_samples);
    void timeLoop();
private:
    unsigned long initial_millis = 0;
    unsigned int curr_sample_n = 0;
    unsigned int n_samples;
};

#endif