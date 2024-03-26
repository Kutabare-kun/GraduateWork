#pragma once

class ActorComponent
{
public:
    ActorComponent(class Object* NewOwner, bool bEnableTicks = false);
    virtual ~ActorComponent() = default;

    virtual void Awake();

    virtual void Start();

    virtual void Update(float DeltaTime);

    virtual void LateUpdate(float DeltaTime);

    virtual void Draw();

    virtual Object* GetOwner() const { return Owner; }

    bool IsEnableTicks() const { return bEnableTicks; }

protected:
    bool bEnableTicks = false;
    
private:
    class Object* Owner = nullptr;
};
