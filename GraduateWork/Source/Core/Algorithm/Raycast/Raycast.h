#pragma once
#include "../Quadtree/Quadtree.h"

class Object;

struct RaycastResult
{
    Object* Collision = nullptr;
};

class Raycast
{
public:
    Raycast(Quadtree& NewQuadtree);

    RaycastResult Cast(const Vector2& From, const Vector2& To, int ExclusionID = -1);
    RaycastResult Cast(const Vector2& From, const Vector2& To, CollisionLayer Layer = CollisionLayer::Default);
    RaycastResult Cast(const Vector2& From, const Vector2& To, const std::vector<CollisionLayer>& Layers);

private:
    Rectangle BuildRectangle(const Vector2& LineStart, const Vector2& LineEnd);
    std::vector<Vector2> BuildLinePoints(const Vector2& From, const Vector2& To);

    Quadtree& Quadtree;
};
