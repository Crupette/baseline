#ifndef TIMER_H
#define TIMER_H 1

#include <time.h>

class Timer {
    clock_t start_, end_;
    double delay_ms_;
public:
    Timer();
    ~Timer();

    void start();
    void stop();

    double getDelayMs();
};

#endif
