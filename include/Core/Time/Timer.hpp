#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

#include "../Common/Types.hpp"

namespace Scramble
{
    class Timer
    {
    using Seconds = std::chrono::duration<I64, std::ratio<1, 1>>;
    using Milliseconds = std::chrono::duration<double, std::ratio<1, 1000>>;
    using Nanoseconds = std::chrono::duration<double, std::ratio<1, 1000000000>>;
    using HighResClock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<HighResClock, Nanoseconds>;

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
        double EvaluateInMilliseconds();
        double EvaluateInNanoseconds();
    };
}

#endif