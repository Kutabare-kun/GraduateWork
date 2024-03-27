#include "BoxColliderComponent.h"

#include "../../../Object/Object.h"
#include "../../Transform/TransformComponent.h"

BoxColliderComponent::BoxColliderComponent(Object* Owner)
    : ColliderComponent(Owner), Offset({0.0f, 0.0f})
{}

Manifold BoxColliderComponent::Intersects(std::shared_ptr<ColliderComponent> Other)
{
    Manifold Result;

    std::shared_ptr<BoxColliderComponent> BoxColliderComp = std::dynamic_pointer_cast<BoxColliderComponent>(Other);
    if (BoxColliderComp)
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
    auto TransformComp = GetOwner()->GetTransform();

    if (TransformComp->IsStatic()) return;

    const Rectangle& MyRect = GetCollidable();
    const Rectangle& OtherRect = *Collision.Other;

    Vector2 Resolve{0.0f, 0.0f};
    float XDiff = (MyRect.x + MyRect.width * 0.5f) - (OtherRect.x + OtherRect.width * 0.5f);
    float YDiff = (MyRect.y + MyRect.height * 0.5f) - (OtherRect.y + OtherRect.height * 0.5f);

    if (fabs(XDiff) > fabs(YDiff))
    {
        if (XDiff > 0)
        {
            Resolve.x = (MyRect.x + MyRect.width) - OtherRect.x;
        }
        else
        {
            Resolve.x = (MyRect.x) - (OtherRect.x + OtherRect.width);
        }
    }
    else
    {
        if (YDiff > 0)
        {
            Resolve.y = (MyRect.y + MyRect.height) - OtherRect.y;
        }
        else
        {
            Resolve.y = (MyRect.y) - (OtherRect.y + OtherRect.height);
        }
    }

    TransformComp->SetPosition(Resolve);
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
    const Vector2 OwnerPosition = GetOwner()->GetTransform()->GetPosition();

    AABB.x = OwnerPosition.x - (AABB.width / 2.0f) + Offset.x;
    AABB.y = OwnerPosition.y - (AABB.height / 2.0f) + Offset.y;
}
