#pragma once

class ActorComponent
{
public:
    ActorComponent(class Actor* NewOwner, bool bEnableTicks = false);
    virtual ~ActorComponent() = default;
    
    virtual void AttachTo(class Actor* NewOwner);

    virtual void BeginPlay();

    virtual void EventTick(float DeltaTime);

    virtual void Draw();

    virtual Actor* GetOwner() const { return Owner; }

    bool IsEnableTicks() const { return bEnableTicks; }

protected:
    bool bEnableTicks = false;
    
private:
    class Actor* Owner = nullptr;
};
