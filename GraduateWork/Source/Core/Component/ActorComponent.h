#pragma once

class ActorComponent
{
public:
    explicit ActorComponent(class Object* NewOwner);
    virtual ~ActorComponent() = default;

    virtual void Awake();

    virtual void Start();

    virtual void Update(float DeltaTime);

    virtual void LateUpdate(float DeltaTime);

    class Object* GetOwner() const { return Owner; }

private:
    class Object* Owner = nullptr;
};
