#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

#include "../Common/Types.hpp"

namespace Scramble
{
    class Timer
    {
    typedef std::chrono::duration<I64, std::ratio<1, 1>> Seconds;
    typedef std::chrono::duration<I64, std::ratio<1, 1000>> Milliseconds;
    typedef std::chrono::duration<I64, std::ratio<1, 1000000000>> Nanoseconds;

    typedef std::chrono::high_resolution_clock HighResClock;
    typedef std::chrono::time_point<HighResClock, Nanoseconds> TimePoint;

    private:
        TimePoint startTime;

    public:
        Timer() = default;
        Timer(const Timer& other) = delete;
        Timer(const Timer&& other) = delete;

    public:
        void Start();
        void Reset();

    public:
        I64 EvaluateInSeconds();
        I64 EvaluateInMilliseconds();
        I64 EvaluateInNanoseconds();
    };
}

#endif