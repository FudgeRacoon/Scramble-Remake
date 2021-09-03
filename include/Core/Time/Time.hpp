#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>

#include "../Common/Types.hpp"

namespace Scramble
{
    class Time
    {
    using Nanoseconds = std::chrono::duration<I64, std::ratio<1, 1000000000>>;
    using HighResClock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<HighResClock, Nanoseconds>;

    private:
        static TimePoint startTime;
        static TimePoint currentTime;
        static TimePoint previousTime;

    private:
        static double deltaTime;
        static double elapsedTime;
        static double elapsedUnscaledTime;

    private:
        static float timeScale;

    private:
        Time() = delete;
        ~Time() = delete;

    public:
        static void OnStartUp();
        static void OnUpdate();
        static void OnFrameEnd();

    public:
        static double GetDeltaTime();
        static double GetElapsedTime();
        static double GetElapsedUnscaledTime();

    public:
        static float GetTimeScale();
        static void SetTimeScale(float scale);
    };
}

#endif