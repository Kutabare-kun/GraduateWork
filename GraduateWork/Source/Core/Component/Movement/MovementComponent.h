#pragma once
#include <raylib.h>

#include "../ActorComponent.h"

// Forward declaration
class Actor;

class MovementComponent
    : public ActorComponent
{
public:
    MovementComponent(Object* NewOwner);
    MovementComponent(Object* NewOwner, float NewSpeed);
    
    virtual ~MovementComponent() = default;

    void InputValue(float Value, const Vector2& Direction);
    
    void Update(float DeltaTime) override;

protected:
    float Speed = 0.0f;

private:
    Vector2 Direction;
};
