#include "BoxColliderComponent.h"

#include "../../../Object/Object.h"
#include "../../Transform/TransformComponent.h"

BoxColliderComponent::BoxColliderComponent(Object* Owner)
    : ColliderComponent(Owner), AABB(), Offset({0.0f, 0.0f})
{
}

Manifold BoxColliderComponent::Intersects(std::shared_ptr<ColliderComponent> Other)
{
    Manifold Result;

    if (const std::shared_ptr<BoxColliderComponent> BoxColliderComp = std::dynamic_pointer_cast<BoxColliderComponent>(Other))
    {
        const Rectangle& MyRect = GetCollidable();
        const Rectangle& OtherRect = BoxColliderComp->GetCollidable();

        if (CheckCollisionRecs(MyRect, OtherRect))
        {
            Result.bColliding = true;
            Result.Other = &OtherRect;
        }
    }

    return Result;
}

void BoxColliderComponent::ResolveCollision(const Manifold& Collision)
{
    const auto TransformComp = GetOwner()->GetTransform();

    if (TransformComp->IsStatic()) return;

    const Rectangle& MyRect = GetCollidable();
    const Rectangle& OtherRect = *Collision.Other;

    Vector2 Resolve{0.0f, 0.0f};
    const float XDiff = (MyRect.x + MyRect.width * 0.5f) - (OtherRect.x + OtherRect.width * 0.5f);
    const float YDiff = (MyRect.y + MyRect.height * 0.5f) - (OtherRect.y + OtherRect.height * 0.5f);

    if (fabsf(XDiff) > fabsf(YDiff))
    {
        if (XDiff > 0)
        {
            Resolve.x = (OtherRect.x + OtherRect.width) - MyRect.x;
        }
        else
        {
            Resolve.x = -((MyRect.x + MyRect.width) - OtherRect.x);
        }
    }
    else
    {
        if (YDiff > 0)
        {
            Resolve.y = (OtherRect.y + OtherRect.height) - MyRect.y;
        }
        else
        {
            Resolve.y = -((MyRect.y + MyRect.height) - OtherRect.y);
        }
    }

    TransformComp->AddPosition(Resolve);
}

void BoxColliderComponent::SetOffset(const Vector2& NewOffset)
{
    Offset = NewOffset;
}

void BoxColliderComponent::SetOffset(float X, float Y)
{
    Offset = {X, Y};
}

void BoxColliderComponent::SetSize(const Vector2& NewSize)
{
    AABB.width = NewSize.x;
    AABB.height = NewSize.y;
}

void BoxColliderComponent::SetSize(float Width, float Height)
{
    AABB.width = Width;
    AABB.height = Height;
}

void BoxColliderComponent::OnCollisionBeginOverlap(std::shared_ptr<ColliderComponent> Other)
{
}

void BoxColliderComponent::OnCollisionStayOverlap(std::shared_ptr<ColliderComponent> Other)
{
}

void BoxColliderComponent::OnCollisionEndOverlap(std::shared_ptr<ColliderComponent> Other)
{
}

void BoxColliderComponent::SetCollidable(const Rectangle& NewRect)
{
    AABB = NewRect;
    SetPosition();
}

const Rectangle& BoxColliderComponent::GetCollidable()
{
    SetPosition();
    return AABB;
}

void BoxColliderComponent::SetPosition()
{
    if (!GetOwner() || !GetOwner()->GetTransform()) return;

    const Vector2 OwnerPosition = GetOwner()->GetTransform()->GetPosition();

    AABB.x = OwnerPosition.x - (AABB.width / 2.0f) + Offset.x;
    AABB.y = OwnerPosition.y - (AABB.height / 2.0f) + Offset.y;
}
