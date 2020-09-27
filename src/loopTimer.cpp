#include "loopTimer.h"

LoopTimer::LoopTimer(unsigned int n_samples): n_samples(n_samples){

}

void LoopTimer::timeLoop(){
    if (curr_sample_n == 0){
        initial_millis = millis();
    }
    curr_sample_n++;
    if (curr_sample_n == n_samples){
        Serial.print("Average Loop Time: ");
        Serial.println((millis() - initial_millis) / n_samples);
        curr_sample_n = 0;
    }
}