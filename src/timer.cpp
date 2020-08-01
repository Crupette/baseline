#include "timer.h"
#include <cstdio>

Timer::Timer() : start_(0), end_(0), delay_ms_(0){

}

Timer::~Timer(){

}

void Timer::start(){
    start_ = clock();
}

void Timer::stop(){
    end_ = clock();
    delay_ms_ = (((double)(end_ - start_)) / CLOCKS_PER_SEC) * 100000;
}

double Timer::getDelayMs(){
    return delay_ms_;
}
