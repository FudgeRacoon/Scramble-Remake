#include "Core/Time/Time.hpp"
using namespace Scramble;

Time::TimePoint Time::initlizationTime;
Time::TimePoint Time::currentFrameTime;
Time::TimePoint Time::previousFrameTime;

F64 Time::deltaTime = 0.0;
F64 Time::elapsedTime = 0.0;
F64 Time::elapsedUnscaledTime = 0.0;

F32 Time::timeScale = 1.0;

#include "Core/Logger/Logger.hpp"

void Time::OnStartUp()
{
    S_INFO("Time is starting up...");

    initlizationTime = HighResClock::now();
    currentFrameTime = HighResClock::now();
    previousFrameTime = HighResClock::now();
}
void Time::OnUpdate()
{
    deltaTime = 0.0;

    if(timeScale > 0.0)
    {
        currentFrameTime = HighResClock::now();

        Nanoseconds delta = currentFrameTime - previousFrameTime;
        Nanoseconds elapsed = currentFrameTime - initlizationTime; 
        
        deltaTime = delta.count() * (1e-9) * timeScale;
        elapsedTime = elapsed.count() * (1e-9) * timeScale;
        elapsedUnscaledTime = elapsed.count() * (1e-9);
    }
}
void Time::OnFrameEnd()
{
    previousFrameTime = currentFrameTime;
}

F64 Time::GetDeltaTime()
{
    return deltaTime;
}
F64 Time::GetElapsedTime()
{
    return elapsedTime;
}
F64 Time::GetElapsedUnscaledTime()
{
    return elapsedUnscaledTime;
}

F32 Time::GetTimeScale()
{
    return timeScale;
}
void Time::SetTimeScale(F32 scale)
{
    timeScale = scale;
}