#include "TransformComponent.h"

#include <raymath.h>

#include "../../Object/Object.h"

TransformComponent::TransformComponent(Object* NewOwner, const Vector2& NewPosition, const Vector2& NewOrigin,
                                       float NewRotation, Vector2 NewScale)
    : ActorComponent(NewOwner), Position(NewPosition), Origin(NewOrigin), Rotation(NewRotation), Scale(NewScale),
      bIsStatic(false)
{
}

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

void TransformComponent::SetStatic(bool bIsStatic)
{
    this->bIsStatic = bIsStatic;
}

void TransformComponent::SetParent(std::shared_ptr<TransformComponent> NewParent)
{
    Parent = NewParent;
    Parent->AddChild(GetOwner()->GetTransform());
}

void TransformComponent::AddChild(std::shared_ptr<TransformComponent> NewChild)
{
    Children.push_back(NewChild);
}

void TransformComponent::RemoveChild(std::shared_ptr<TransformComponent> Child)
{
    for (auto Iter = Children.begin(); Iter != Children.end(); ++Iter)
    {
        if (auto Component = *Iter;
            Component->GetOwner()->GetInstanceID()->GetID() == Child->GetOwner()->GetInstanceID()->GetID())
        {
            Children.erase(Iter);
            break;
        }
    }
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
