#pragma once
#include <memory>
#include <vector>

#include "../Timer.h"

class TimerManager
{
public:
    TimerManager() = default;

    void Update(float DeltaTime);

    void AddTimer(const TimerCallback& Callback, float MaxTime, bool bLoop = false);

protected:
    bool Sort(const std::unique_ptr<Timer>& A, const std::unique_ptr<Timer>& B) const;

private:
    std::vector<std::unique_ptr<Timer>> Timers;
};
