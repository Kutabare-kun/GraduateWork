#include "MovementComponent.h"

#include <raymath.h>

#include "../../Object/Actor/Actor.h"
#include "../Transform/TransformComponent.h"

MovementComponent::MovementComponent(Object* NewOwner)
    : ActorComponent(NewOwner, true)
{}

MovementComponent::MovementComponent(Object* NewOwner, float NewSpeed)
    : ActorComponent(NewOwner, true),
    Speed(NewSpeed)
{}

void MovementComponent::InputValue(float Value, const Vector2& Direction)
{
    this->Direction = Vector2Scale(Direction, Value);
}

void MovementComponent::Update(float DeltaTime)
{
    ActorComponent::Update(DeltaTime);
    
    if (Speed <= 0.0f) return;
    if (Vector2Length(Direction) <= 0.0f) return;

    const Vector2 Velocity = Vector2Scale(Direction, Speed * DeltaTime);
    auto OwnerTransform = GetOwner()->GetComponent<TransformComponent>();
    OwnerTransform->AddPosition(Velocity);

    Direction = Vector2Zero();
}
