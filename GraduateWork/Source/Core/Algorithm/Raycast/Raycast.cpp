#include "Raycast.h"

#include <raymath.h>

#include "../../StaticFunctions/Debug.h"
#include "../../Object/Object.h"

Raycast::Raycast(::Quadtree& NewQuadtree)
    : Quadtree(NewQuadtree)
{}

RaycastResult Raycast::Cast(const Vector2& From, const Vector2& To, int ExclusionID)
{
    RaycastResult Result;

    if (Vector2Equals(From, To))
    {
        return Result;
    }

    Rectangle CollisionArea = BuildRectangle(From, To);
    // Debug::GetInstance().DrawRectangle(CollisionArea, RED);

    std::vector<std::shared_ptr<BoxColliderComponent>> Entities = Quadtree.Search(CollisionArea);
    if (Entities.empty())
    {
        return Result;
    }

    std::vector<Vector2> LinePoints = BuildLinePoints(From, To);
    for (auto& Point : LinePoints)
    {
        for (auto& Entity : Entities)
        {
            if (static_cast<int>(Entity->GetOwner()->GetInstanceID()->GetID()) == ExclusionID)
            {
                continue;
            }
            
            if (const Rectangle& EntityRect = Entity->GetCollidable(); CheckCollisionPointRec(Point, EntityRect))
            {
                Result.Collision = Entity->GetOwner();
                return Result;
            }
        }
    }

    return Result;
}

Rectangle Raycast::BuildRectangle(const Vector2& LineStart, const Vector2& LineEnd)
{
    constexpr float RectWidth = 0.2f;
    constexpr float HalfWidth = RectWidth / 2.0f;
    
    float Left, Top, Width, Height;

    if (LineStart.x == LineEnd.x)
    {
        Left = LineStart.x - HalfWidth;
        Top = (LineStart.y < LineEnd.y) ? LineStart.y : LineEnd.y;
        Width = RectWidth;
        Height = fabsf(LineEnd.y - LineStart.y);
    }
    else
    {
        Left = (LineStart.x < LineEnd.x) ? LineStart.x : LineEnd.x;
        Top = LineStart.y - HalfWidth;
        Width = fabsf(LineEnd.x - LineStart.x);
        Height = RectWidth;
    }

    return Rectangle{Left, Top, Width, Height};
}

std::vector<Vector2> Raycast::BuildLinePoints(const Vector2& From, const Vector2& To)
{
    std::vector<Vector2> Result;

    const Vector2 Difference = Vector2Subtract(To, From);
    const float AbsDifferenceX = fabsf(Difference.x);
    const float AbsDifferenceY = fabsf(Difference.y);

    int Steps{};
    if (AbsDifferenceX > AbsDifferenceY)
    {
        Steps = static_cast<int>(AbsDifferenceX);
    }
    else
    {
        Steps = static_cast<int>(AbsDifferenceY);
    }

    const float XStep = Difference.x / static_cast<float>(Steps);
    const float YStep = Difference.y / static_cast<float>(Steps);

    float NewX = From.x;
    float NewY = From.y;

    for (int Index = 0; Index < Steps; ++Index)
    {
        Result.emplace_back(NewX, NewY);

        NewX += XStep;
        NewY += YStep;
    }

    return Result;
}
