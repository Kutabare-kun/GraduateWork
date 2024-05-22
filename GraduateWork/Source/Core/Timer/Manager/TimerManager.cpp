#include "TimerManager.h"

#include <algorithm>

void TimerManager::Update(float DeltaTime)
{
    for (auto Iter = Timers.begin(); Iter != Timers.end();)
    {
        (*Iter)->Update(DeltaTime);

        if ((*Iter)->IsElapsed())
        {
            Iter = Timers.erase(Iter);
        }
        else
        {
            ++Iter;
        }
    }
}

std::shared_ptr<Timer> TimerManager::AddTimer(const TimerCallback& Callback, float MaxTime, bool bLoop)
{
    std::shared_ptr<Timer> MyTimer = std::make_shared<Timer>(Callback, MaxTime, bLoop);

    auto Iter = std::ranges::lower_bound(Timers, MyTimer,
                                         [this](const auto& A, const auto& B) -> bool
                                         {
                                             return this->Sort(A, B);
                                         });

    Timers.emplace(Iter, MyTimer);
    Timers.shrink_to_fit();

    return MyTimer;
}

bool TimerManager::Sort(const std::shared_ptr<Timer>& A, const std::shared_ptr<Timer>& B) const
{
    return A->RemainingTime() < B->RemainingTime();
}
