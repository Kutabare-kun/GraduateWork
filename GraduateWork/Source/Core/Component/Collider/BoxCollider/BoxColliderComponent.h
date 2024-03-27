#pragma once
#include "../ColliderComponent.h"

class BoxColliderComponent
    : public ColliderComponent
{
public:
    BoxColliderComponent(Object* Owner);

    Manifold Intersects(std::shared_ptr<ColliderComponent> Other) override;
    void ResolveCollision(const Manifold& Collision) override;

    void SetCollidable(const Rectangle& NewRect);
    const Rectangle& GetCollidable();

private:
    void SetPosition();

    Rectangle AABB;
    Vector2 Offset;
};
