#include "Timer.h"

using namespace std;

void Timer::start(){
    startTime = chrono::high_resolution_clock::now();
}

double Timer::stop(){
    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration<double, milli>(endTime - startTime);
    return duration.count();
}