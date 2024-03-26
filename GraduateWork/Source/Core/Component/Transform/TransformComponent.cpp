#include "TransformComponent.h"

#include <raymath.h>

TransformComponent::TransformComponent(Object* NewOwner, const Vector2& NewPosition, const Vector2& NewOrigin,
                                       float NewRotation, Vector2 NewScale)
    : ActorComponent(NewOwner), Position(NewPosition), Origin(NewOrigin), Rotation(NewRotation), Scale(NewScale)
{}

void TransformComponent::SetPosition(const Vector2& NewPosition)
{
    Position = NewPosition;
}

void TransformComponent::SetRotation(float NewRotation)
{
    Rotation = NewRotation;
}

void TransformComponent::SetScale(Vector2 NewScale)
{
    Scale = NewScale;
}

void TransformComponent::SetOrigin(const Vector2& NewOrigin)
{
    Origin = NewOrigin;
}

void TransformComponent::AddPosition(const Vector2& DeltaPosition)
{
    Position = Vector2Add(Position, DeltaPosition);
}

void TransformComponent::AddRotation(float DeltaRotation)
{
    Rotation = fmodf(Rotation + DeltaRotation, 360.0f);
}

void TransformComponent::AddScale(Vector2 DeltaScale)
{
    Scale = Vector2Add(Scale, DeltaScale);
}

void TransformComponent::AddOrigin(const Vector2& DeltaOrigin)
{
    Origin = Vector2Add(Origin, DeltaOrigin);
}
