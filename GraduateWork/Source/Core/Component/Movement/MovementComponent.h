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
    
    virtual ~MovementComponent() override = default;

    void InputValue(float Value, const Vector2& Direction);

    void Awake() override;
    
    void Update(float DeltaTime) override;

    Vector2 GetDirection() const { return LastDirection; }
    Vector2 GetHeading() const { return Heading; }

    float GetSpeed() const { return Speed; }

    bool IsEnabled() const { return bIsEnabled; }
    void SetEnabled(bool bNewEnabled) { bIsEnabled = bNewEnabled; }

    void SetSpeed(float NewSpeed) { Speed = NewSpeed; }

protected:
    float Speed = 0.0f;
    const float* SpeedPtr = nullptr;

private:
    Vector2 LastDirection = {};
    Vector2 Heading = {};
    Vector2 Direction = {};

    bool bIsEnabled;

    std::shared_ptr<AnimationComponent> Animation;
};
