#pragma once
#include "../ColliderComponent.h"

class BoxColliderComponent
    : public ColliderComponent
{
public:
    BoxColliderComponent(Object* Owner);

    Manifold Intersects(std::shared_ptr<ColliderComponent> Other) override;
    void ResolveCollision(const Manifold& Collision) override;

    void SetOffset(const Vector2& NewOffset);
    void SetOffset(float X, float Y);

    void SetSize(const Vector2& NewSize);
    void SetSize(float Width, float Height);

    void OnCollisionBeginOverlap(std::shared_ptr<ColliderComponent> Other) override;
    void OnCollisionStayOverlap(std::shared_ptr<ColliderComponent> Other) override;
    void OnCollisionEndOverlap(std::shared_ptr<ColliderComponent> Other) override;

    void SetCollidable(const Rectangle& NewRect);
    const Rectangle& GetCollidable();

private:
    void SetPosition();

    Rectangle AABB;
    Vector2 Offset;
};
