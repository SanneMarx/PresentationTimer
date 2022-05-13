#ifndef _TIMER_INTERFACE_H_
#define _TIMER_INTERFACE_H_

#ifdef ESP8266

#else
    #include <chrono>
    #include <algorithm>

    
    using namespace std::chrono;
    #define millis duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count
#endif

#endif
