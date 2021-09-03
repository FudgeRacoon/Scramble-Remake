#include "Core/Time/Time.hpp"
using namespace Scramble;

Time::TimePoint Time::startTime;
Time::TimePoint Time::currentTime;
Time::TimePoint Time::previousTime;

double Time::deltaTime = 0.0;
double Time::elapsedTime = 0.0;
double Time::elapsedUnscaledTime = 0.0;

float Time::timeScale = 1.0;

void Time::OnStartUp()
{
    startTime = HighResClock::now();
    currentTime = HighResClock::now();
    previousTime = HighResClock::now();
}
void Time::OnUpdate()
{
    deltaTime = 0.0;

    if(timeScale > 0.0)
    {
        currentTime = HighResClock::now();

        Nanoseconds delta = std::chrono::duration_cast<Nanoseconds>(
            currentTime - previousTime
        );
        Nanoseconds elapsed = std::chrono::duration_cast<Nanoseconds>(
            currentTime - startTime
        );

        deltaTime = delta.count() * (1e-9) * timeScale;
        elapsedTime += deltaTime;
        elapsedUnscaledTime += elapsed.count() * (1e-9);
    }
}
void Time::OnFrameEnd()
{
    previousTime = currentTime;
}

double Time::GetDeltaTime()
{
    return deltaTime;
}
double Time::GetElapsedTime()
{
    return elapsedTime;
}
double Time::GetElapsedUnscaledTime()
{
    return elapsedUnscaledTime;
}

float Time::GetTimeScale()
{
    return timeScale;
}
void Time::SetTimeScale(float scale)
{
    timeScale = scale;
}