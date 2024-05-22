#include "Raycast.h"

#include <raymath.h>
#include <algorithm>

#include "../../StaticFunctions/Debug.h"
#include "../../Object/Object.h"

Raycast::Raycast(::Quadtree& NewQuadtree)
    : Quadtree(NewQuadtree)
{
}

RaycastResult Raycast::Cast(const Vector2& From, const Vector2& To, int ExclusionID)
{
    RaycastResult Result;

    if (Vector2Equals(From, To))
    {
        return Result;
    }

    Rectangle CollisionArea = BuildRectangle(From, To);

    std::vector<std::shared_ptr<BoxColliderComponent>> Entities = Quadtree.Search(CollisionArea);
    if (Entities.empty())
    {
        return Result;
    }

    std::vector<std::pair<Vector2, Object*>> CollidedPoints;

    std::pair<Vector2, Vector2> Line = std::make_pair(From, To);
    for (auto& Entity : Entities)
    {
        if (static_cast<int>(Entity->GetOwner()->GetInstanceID()->GetID()) == ExclusionID) continue;

        const Rectangle& EntityRect = Entity->GetCollidable();
        std::pair<Vector2, Vector2> MainDiagonal = std::make_pair<Vector2, Vector2>(
            {EntityRect.x, EntityRect.y},
            {EntityRect.x + EntityRect.width, EntityRect.y + EntityRect.height}
        );

        std::pair<Vector2, Vector2> SecondaryDiagonal = std::make_pair<Vector2, Vector2>(
            {EntityRect.x + EntityRect.width, EntityRect.y},
            {EntityRect.x, EntityRect.y + EntityRect.height}
        );

        Vector2 CollisionPoint{};
        CheckCollisionLines(Line.first, Line.second, MainDiagonal.first, MainDiagonal.second, &CollisionPoint);
        if (!Vector2Equals(CollisionPoint, Vector2Zero()))
        {
            CollidedPoints.emplace_back(CollisionPoint, Entity->GetOwner());
        }

        CheckCollisionLines(Line.first, Line.second, SecondaryDiagonal.first, SecondaryDiagonal.second,
                            &CollisionPoint);
        if (!Vector2Equals(CollisionPoint, Vector2Zero()))
        {
            CollidedPoints.emplace_back(CollisionPoint, Entity->GetOwner());
        }
    }

    std::ranges::sort(CollidedPoints, [&From](const auto& A, const auto& B)
    {
        return Vector2Distance(From, A.first) < Vector2Distance(From, B.first);
    });

    if (!CollidedPoints.empty())
    {
        Result.Collision = CollidedPoints[0].second;
        return Result;
    }

    for (const std::vector<Vector2> LinePoints = BuildLinePoints(From, To); auto& Point : LinePoints)
    {
        // Debug::GetInstance().DrawPixel(Point, BLUE);
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

RaycastResult Raycast::Cast(const Vector2& From, const Vector2& To, CollisionLayer Layer)
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

    std::vector<std::pair<Vector2, Object*>> CollidedPoints;

    std::pair<Vector2, Vector2> Line = std::make_pair(From, To);
    for (auto& Entity : Entities)
    {
        if (Entity->GetLayer() == Layer) continue;

        const Rectangle& EntityRect = Entity->GetCollidable();
        std::pair<Vector2, Vector2> MainDiagonal = std::make_pair<Vector2, Vector2>(
            {EntityRect.x, EntityRect.y},
            {EntityRect.x + EntityRect.width, EntityRect.y + EntityRect.height}
        );

        std::pair<Vector2, Vector2> SecondaryDiagonal = std::make_pair<Vector2, Vector2>(
            {EntityRect.x + EntityRect.width, EntityRect.y},
            {EntityRect.x, EntityRect.y + EntityRect.height}
        );

        Vector2 CollisionPoint{};
        CheckCollisionLines(Line.first, Line.second, MainDiagonal.first, MainDiagonal.second, &CollisionPoint);
        if (!Vector2Equals(CollisionPoint, Vector2Zero()))
        {
            CollidedPoints.emplace_back(CollisionPoint, Entity->GetOwner());
        }

        CheckCollisionLines(Line.first, Line.second, SecondaryDiagonal.first, SecondaryDiagonal.second,
                            &CollisionPoint);
        if (!Vector2Equals(CollisionPoint, Vector2Zero()))
        {
            CollidedPoints.emplace_back(CollisionPoint, Entity->GetOwner());
        }
    }

    std::ranges::sort(CollidedPoints, [&From](const auto& A, const auto& B)
    {
        return Vector2Distance(From, A.first) < Vector2Distance(From, B.first);
    });

    if (!CollidedPoints.empty())
    {
        Result.Collision = CollidedPoints[0].second;
        return Result;
    }

    return Result;
}

RaycastResult Raycast::Cast(const Vector2& From, const Vector2& To, const std::vector<CollisionLayer>& Layers)
{
    RaycastResult Result;

    if (Vector2Equals(From, To))
    {
        return Result;
    }

    Rectangle CollisionArea = BuildRectangle(From, To);

    std::vector<std::shared_ptr<BoxColliderComponent>> Entities = Quadtree.Search(CollisionArea);
    if (Entities.empty())
    {
        return Result;
    }

    std::vector<std::pair<Vector2, Object*>> CollidedPoints;

    std::pair<Vector2, Vector2> Line = std::make_pair(From, To);
    for (auto& Entity : Entities)
    {
        bool bFound = false;
        for (const auto& Layer : Layers)
        {
            if (Entity->GetLayer() == Layer)
            {
                bFound = true;
                break;
            }
        }
        if (bFound) continue;

        const Rectangle& EntityRect = Entity->GetCollidable();
        std::pair<Vector2, Vector2> MainDiagonal = std::make_pair<Vector2, Vector2>(
            {EntityRect.x, EntityRect.y},
            {EntityRect.x + EntityRect.width, EntityRect.y + EntityRect.height}
        );

        std::pair<Vector2, Vector2> SecondaryDiagonal = std::make_pair<Vector2, Vector2>(
            {EntityRect.x + EntityRect.width, EntityRect.y},
            {EntityRect.x, EntityRect.y + EntityRect.height}
        );

        Vector2 CollisionPoint{};
        CheckCollisionLines(Line.first, Line.second, MainDiagonal.first, MainDiagonal.second, &CollisionPoint);
        if (!Vector2Equals(CollisionPoint, Vector2Zero()))
        {
            CollidedPoints.emplace_back(CollisionPoint, Entity->GetOwner());
        }

        CheckCollisionLines(Line.first, Line.second, SecondaryDiagonal.first, SecondaryDiagonal.second,
                            &CollisionPoint);
        if (!Vector2Equals(CollisionPoint, Vector2Zero()))
        {
            CollidedPoints.emplace_back(CollisionPoint, Entity->GetOwner());
        }
    }

    std::ranges::sort(CollidedPoints, [&From](const auto& A, const auto& B)
    {
        return Vector2Distance(From, A.first) < Vector2Distance(From, B.first);
    });

    if (!CollidedPoints.empty())
    {
        Result.Collision = CollidedPoints[0].second;
        return Result;
    }

    return Result;
}

Rectangle Raycast::BuildRectangle(const Vector2& LineStart, const Vector2& LineEnd)
{
    const float Left = (LineStart.x < LineEnd.x) ? LineStart.x : LineEnd.x;
    const float Top = (LineStart.y < LineEnd.y) ? LineStart.y : LineEnd.y;
    const float Width = fabsf(LineStart.x - LineEnd.x);
    const float Height = fabsf(LineStart.y - LineEnd.y);

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
