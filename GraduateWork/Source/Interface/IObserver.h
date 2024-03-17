#pragma once

// Interface for the Observer
class IObserver
{
public:
    virtual ~IObserver() = default;
    virtual void Update() = 0;
};
