#include "VelocityComponent.h"
#include "../../Object/Object.h"

#include <raymath.h>

#include "../../StaticFunctions/Debug.h"

VelocityComponent::VelocityComponent(Object* NewOwner)
    : ActorComponent(NewOwner), Velocity(), MaxVelocity(-500.0f, 500.0f)
{
}

void VelocityComponent::Update(float DeltaTime)
{
    ActorComponent::Update(DeltaTime);

    GetOwner()->GetTransform()->AddPosition(Vector2Scale(Velocity, DeltaTime));
}

void VelocityComponent::SetVelocity(const Vector2& NewVelocity)
{
    Velocity = NewVelocity;
    ClampVelocity();

    Debug::GetInstance().Log(TextFormat("%s, Velocity: %f, %f", GetOwner()->GetName().c_str(), Velocity.x, Velocity.y));
}

void VelocityComponent::SetVelocity(float X, float Y)
{
    Velocity = {X, Y};
    ClampVelocity();
}

void VelocityComponent::ClampVelocity()
{
    Vector2Clamp(Velocity, Vector2Negate(MaxVelocity), MaxVelocity);
}
