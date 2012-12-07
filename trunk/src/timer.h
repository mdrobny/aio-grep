#ifndef TIMER_H
#define TIMER_H
#include<ctime>
#include<iostream>


class Timer
{
    clock_t start;
public:
    Timer();
    ~Timer();
    time_t getTime();
};

#endif // TIMER_H
