#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>

#include "../Common/Types.hpp"

namespace Scramble
{
    class Time
    {
    typedef std::chrono::seconds Seconds;
    typedef std::chrono::nanoseconds Nanoseconds;
    
    typedef std::chrono::high_resolution_clock HighResClock;
    typedef std::chrono::time_point<HighResClock,Nanoseconds > TimePoint;

    private:
        static TimePoint initlizationTime;
        static TimePoint currentFrameTime;
        static TimePoint previousFrameTime;

    private:
        static F64 deltaTime;
        static F64 elapsedTime;
        static F64 elapsedUnscaledTime;

    private:
        static F32 timeScale;

    private:
        Time() = delete;
        ~Time() = delete;

    public:
        static void OnStartUp();
        static void OnUpdate();
        static void OnFrameEnd();

        static F64 GetDeltaTime();
        static F64 GetElapsedTime();
        static F64 GetElapsedUnscaledTime();

    public:
        static F32 GetTimeScale();
        static void SetTimeScale(F32 scale);
    };
}

#endif