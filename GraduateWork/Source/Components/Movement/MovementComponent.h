#pragma once
#include <raylib.h>

#include "../../Core/Component/ActorComponent.h"

// Forward declaration
class Actor;

class MovementComponent
    : public ActorComponent
{
public:
    MovementComponent(Actor* NewOwner);
    MovementComponent(Actor* NewOwner, float NewSpeed);
    
    virtual ~MovementComponent() = default;

    virtual void EventTick(float DeltaTime) override;

    virtual void InputValue(float Value, const Vector2& Direction);

    // Getters
    Vector2& GetVelocity() { return Velocity; }
    const Vector2& GetVelocity() const { return Velocity; }
    
    float GetSpeed() const { return Speed; }

    Vector2 GetDirection() const { return MovementDirection; }
    // ~Getters

    // Setters
    void SetSpeed(float NewSpeed) { Speed = NewSpeed; }
    // ~Setters

protected:
    Vector2 Velocity = {};
    float Speed = 0.0f;

    Vector2 MovementDirection = {};
};
