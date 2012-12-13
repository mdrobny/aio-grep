#include "timer.h"

Timer::Timer()
{
    start = clock();
    //std::cout << "start!\n";
}

Timer::~Timer()
{
    //std::cout << "Executing time: " << clock() - start << std::endl;
}

time_t Timer::getTime()
{
    return clock() - start;
}
