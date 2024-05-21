#pragma once
#include <memory>
#include <vector>

#include "../Timer.h"

class TimerManager
{
public:
    TimerManager() = default;

    void Update(float DeltaTime);

    std::shared_ptr<Timer> AddTimer(const TimerCallback& Callback, float MaxTime, bool bLoop = false);

protected:
    bool Sort(const std::shared_ptr<Timer>& A, const std::shared_ptr<Timer>& B) const;

private:
    std::vector<std::shared_ptr<Timer>> Timers;
};
