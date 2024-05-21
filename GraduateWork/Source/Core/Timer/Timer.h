#pragma once
#include <functional>

using TimerCallback = std::function<void(void)>;

class Timer
{
public:
    Timer(const TimerCallback& Callback, float MaxTime, bool bLoop = false);

    void Update(float DeltaTime);

    void Elapsed();

    void UpdateTimer(float NewMaxTime);
    void UpdateTimer(bool bNewLoop);

    bool IsLoop() const { return bLoop; }
    bool IsElapsed() const { return bElapsed; }
    float RemainingTime() const { return MaxTime - CurrentTime; }

private:
    bool bLoop;

    float MaxTime;
    float CurrentTime;

    TimerCallback Callback;

    bool bElapsed;
};
