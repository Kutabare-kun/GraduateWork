#include "MovementComponent.h"

#include <raymath.h>

#include "../../Object/Actor/Actor.h"
#include "../Transform/TransformComponent.h"
#include "../Animation/AnimationComponent.h"

MovementComponent::MovementComponent(Object* NewOwner)
    : ActorComponent(NewOwner, true)
{}

MovementComponent::MovementComponent(Object* NewOwner, float NewSpeed)
    : ActorComponent(NewOwner, true),
    Speed(NewSpeed)
{}

void MovementComponent::InputValue(float Value, const Vector2& Direction)
{
    this->Direction = Vector2Add(Vector2Scale(Direction, Value), this->Direction);

    if (this->Direction.x > 0.0f)
    {
        Animation->SetAnimationDirection(FacingDirection::Right);
    }
    else if (this->Direction.x < 0.0f)
    {
        Animation->SetAnimationDirection(FacingDirection::Left);
    }
}

void MovementComponent::Awake()
{
    ActorComponent::Awake();

    Animation = GetOwner()->GetComponent<AnimationComponent>();
}

void MovementComponent::Update(float DeltaTime)
{
    ActorComponent::Update(DeltaTime);
    
    if (Speed <= 0.0f) return;
    if (Vector2Length(Direction) <= 0.0f)
    {
        Animation->SetAnimationState(AnimationState::Idle);
        return;
    }

    Animation->SetAnimationState(AnimationState::Walk);

    const Vector2 Velocity = Vector2Scale(Direction, Speed * DeltaTime);
    auto OwnerTransform = GetOwner()->GetTransform();
    OwnerTransform->AddPosition(Velocity);

    Direction = Vector2Zero();
}
