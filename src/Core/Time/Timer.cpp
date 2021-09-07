#include "Core/Time/Timer.hpp"
using namespace Scramble;

void Timer::Start()
{
    this->startTime = HighResClock::now();
}
void Timer::Reset()
{
    this->startTime = HighResClock::now();
}

I64 Timer::EvaluateInSeconds()
{
    Seconds elapsed = std::chrono::duration_cast<Seconds>(
        HighResClock::now() - this->startTime
    );

    return elapsed.count();
}
I64 Timer::EvaluateInMilliseconds()
{
    Milliseconds elapsed = std::chrono::duration_cast<Milliseconds>(
        HighResClock::now() - this->startTime
    );

    return elapsed.count();
}   
I64 Timer::EvaluateInNanoseconds()
{
    Nanoseconds elapsed = HighResClock::now() - this->startTime;

    return elapsed.count();
}