#include "MovementComponent.h"

#include <raymath.h>

#include "../../Object/Actor/Actor.h"
#include "../Transform/TransformComponent.h"
#include "../Animation/AnimationComponent.h"

MovementComponent::MovementComponent(Object* NewOwner)
    : ActorComponent(NewOwner), bIsEnabled(true)
{}

MovementComponent::MovementComponent(Object* NewOwner, float NewSpeed)
    : ActorComponent(NewOwner),
    Speed(NewSpeed), bIsEnabled(true)
{}

void MovementComponent::InputValue(float Value, const Vector2& Direction)
{
    this->Direction = Vector2Add(Vector2Scale(Direction, Value), this->Direction);

    if (!Animation) return;

    if (this->Direction.x > 0.0f)
    {
        Animation->SetAnimationDirection(FacingDirection::Right);
        Heading = {1.0f, 0.0f};
    }
    else if (this->Direction.x < 0.0f)
    {
        Animation->SetAnimationDirection(FacingDirection::Left);
        Heading = {-1.0f, 0.0f};
    }
    else if (this->Direction.y > 0.0f)
    {
        Animation->SetAnimationDirection(FacingDirection::Down);
        Heading = {0.0f, 1.0f};
    }
    else if (this->Direction.y < 0.0f)
    {
        Animation->SetAnimationDirection(FacingDirection::Up);
        Heading = {0.0f, -1.0f};
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

    if (Vector2Length(Direction) > 0.0f)
        LastDirection = Direction;
    Direction = Vector2Zero();
}
