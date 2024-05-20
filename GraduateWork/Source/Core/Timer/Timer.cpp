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
