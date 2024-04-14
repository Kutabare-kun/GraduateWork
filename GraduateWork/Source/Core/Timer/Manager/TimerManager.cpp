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

void TimerManager::AddTimer(const TimerCallback& Callback, float MaxTime, bool bLoop)
{
    std::unique_ptr<Timer> MyTimer = std::make_unique<Timer>(Callback, MaxTime, bLoop);
    
    auto Iter = std::ranges::lower_bound(Timers, MyTimer,
        [this](const auto& A, const auto& B) -> bool
    {
        return this->Sort(A, B);
    });
    
    Timers.emplace(Iter, std::move(MyTimer));
    Timers.shrink_to_fit();
}

bool TimerManager::Sort(const std::unique_ptr<Timer>& A, const std::unique_ptr<Timer>& B) const
{
    return A->RemainingTime() < B->RemainingTime();
}
