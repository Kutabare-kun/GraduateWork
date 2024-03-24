#include "TransformComponent.h"

#include <raymath.h>

TransformComponent::TransformComponent(Actor* NewOwner, const Vector2& NewPosition, float NewRotation, float NewScale)
    : ActorComponent(NewOwner), Position(NewPosition), Rotation(NewRotation), Scale(NewScale)
{}

void TransformComponent::SetPosition(const Vector2& NewPosition)
{
    Position = NewPosition;
}

void TransformComponent::SetRotation(float NewRotation)
{
    Rotation = NewRotation;
}

void TransformComponent::SetScale(float NewScale)
{
    Scale = NewScale;
}

void TransformComponent::AddPosition(const Vector2& DeltaPosition)
{
    Position = Vector2Add(Position, DeltaPosition);
}

void TransformComponent::AddRotation(float DeltaRotation)
{
    Rotation = fmodf(Rotation + DeltaRotation, 360.0f);
}

void TransformComponent::AddScale(float DeltaScale)
{
    Scale += DeltaScale;
}
