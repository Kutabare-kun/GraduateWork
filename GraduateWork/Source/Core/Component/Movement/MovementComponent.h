#pragma once
#include <memory>
#include <raylib.h>

#include "../ActorComponent.h"

// Forward declaration
class AnimationComponent;
class Actor;

class MovementComponent
    : public ActorComponent
{
public:
    explicit MovementComponent(Object* NewOwner);
    MovementComponent(Object* NewOwner, float NewSpeed);
    
    virtual ~MovementComponent() = default;

    void InputValue(float Value, const Vector2& Direction);

    void Awake() override;
    
    void Update(float DeltaTime) override;

    float GetSpeed() const { return Speed; }

    void SetSpeed(float NewSpeed) { Speed = NewSpeed; }

protected:
    float Speed = 0.0f;

private:
    Vector2 Direction = {};

    std::shared_ptr<AnimationComponent> Animation;
};
