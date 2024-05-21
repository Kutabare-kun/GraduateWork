#include "Timer.h"

Timer::Timer(const TimerCallback& Callback, float MaxTime, bool bLoop)
    : bLoop(bLoop), MaxTime(MaxTime), CurrentTime(0.0f), Callback(Callback), bElapsed(false)
{
}

void Timer::Update(float DeltaTime)
{
    CurrentTime += DeltaTime;

    if (CurrentTime >= MaxTime && (!bElapsed || bLoop))
    {
        bElapsed = true;

        Elapsed();
    }
}

void Timer::Elapsed()
{
    Callback();

    if (!bLoop) return;
    CurrentTime = 0.0f;
}

void Timer::UpdateTimer(float NewMaxTime)
{
    MaxTime = NewMaxTime;
    CurrentTime = 0.0f;
    bElapsed = false;
}

void Timer::UpdateTimer(bool bNewLoop)
{
    bLoop = bNewLoop;
    CurrentTime = 0.0f;
    bElapsed = false;
}
