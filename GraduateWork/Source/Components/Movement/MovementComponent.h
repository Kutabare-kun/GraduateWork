#pragma once
#include <raylib.h>

// Forward declaration
class Actor;

class MovementComponent
{
public:
    MovementComponent() = default;
    MovementComponent(Actor* NewOwner);
    MovementComponent(Actor* NewOwner, float NewSpeed, float NewMaxSpeed);
    
    virtual ~MovementComponent() = default;
    
    void AttachTo(Actor* NewOwner);

    virtual void EventTick(float DeltaTime);

    virtual void InputValue(float Value, const Vector2& Direction);

    // Getters
    Vector2& GetVelocity() { return Velocity; }
    const Vector2& GetVelocity() const { return Velocity; }
    
    float GetSpeed() const { return Speed; }
    float GetMaxSpeed() const { return MaxSpeed; }

    Vector2 GetDirection() const { return MovementDirection; }
    // ~Getters

    // Setters
    void SetSpeed(float NewSpeed) { Speed = NewSpeed; }
    void SetMaxSpeed(float NewMaxSpeed) { MaxSpeed = NewMaxSpeed; }
    // ~Setters

protected:
    Vector2 Velocity = {};
    float Speed = 0.0f;
    float MaxSpeed = 0.0f;

    Vector2 MovementDirection = {};

private:
    Actor* Owner = nullptr;
};
