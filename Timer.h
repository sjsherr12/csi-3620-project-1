#ifndef TIMER_H
#define TIMER_H

#include <chrono>

using namespace std;

class Timer{
private:
    chrono::high_resolution_clock::time_point startTime;
public:
    void start();
    double stop();
};

#endif