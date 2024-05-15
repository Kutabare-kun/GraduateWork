#pragma once
#include "../ActorComponent.h"

#include <raylib.h>

class VelocityComponent
    : public ActorComponent
{
public:
    explicit VelocityComponent(Object* NewOwner);

    void Update(float DeltaTime) override;

    void SetVelocity(const Vector2& NewVelocity);
    void SetVelocity(float X, float Y);
    Vector2 GetVelocity() const { return Velocity; }

private:
    void ClampVelocity();

    Vector2 Velocity;
    Vector2 MaxVelocity;
};
