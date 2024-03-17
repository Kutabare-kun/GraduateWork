#pragma once

// Forward declaration
class IObserver;

// Interface for the Subject
class ISubject
{
public:
    virtual ~ISubject() = default;
    virtual void Attach(IObserver* Observer) = 0;
    virtual void Detach(IObserver* Observer) = 0;
    virtual void Notify() = 0;
};
