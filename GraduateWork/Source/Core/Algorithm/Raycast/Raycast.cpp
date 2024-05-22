#include "Raycast.h"

#include <raymath.h>
#include <algorithm>

#include "../../Object/Object.h"

Raycast::Raycast(::Quadtree& NewQuadtree)
    : Quadtree(NewQuadtree)
{
}

std::vector<std::pair<Vector2, Vector2>> Raycast::MakeLinesFromRectangle(const Rectangle& EntityRect)
{
    const std::vector<std::pair<Vector2, Vector2>> RectangleLines = {
        // TopLeft, TopRight
        std::make_pair<Vector2, Vector2>(
            {EntityRect.x, EntityRect.y},
            {EntityRect.x + EntityRect.width, EntityRect.y}
        ),
        // TopRight, BottomRight
        std::make_pair<Vector2, Vector2>(
            {EntityRect.x + EntityRect.width, EntityRect.y},
            {EntityRect.x + EntityRect.width, EntityRect.y + EntityRect.height}
        ),
        // BottomRight, BottomLeft
        std::make_pair<Vector2, Vector2>(
            {EntityRect.x + EntityRect.width, EntityRect.y + EntityRect.height},
            {EntityRect.x, EntityRect.y + EntityRect.height}
        ),
        // BottomLeft, TopLeft
        std::make_pair<Vector2, Vector2>(
            {EntityRect.x, EntityRect.y + EntityRect.height},
            {EntityRect.x, EntityRect.y}
        )
    };

    return RectangleLines;
}

RaycastResult Raycast::Cast(const Vector2& From, const Vector2& To, int ExclusionID)
{
    RaycastResult Result;

    if (Vector2Equals(From, To))
    {
        return Result;
    }

    const Rectangle CollisionArea = BuildRectangle(From, To);

    const std::vector<std::shared_ptr<BoxColliderComponent>> Entities = Quadtree.Search(CollisionArea);
    if (Entities.empty())
    {
        return Result;
    }

    std::vector<std::pair<Vector2, Object*>> CollidedPoints;

    const std::pair<Vector2, Vector2> Line = std::make_pair(From, To);
    for (const auto& Entity : Entities)
    {
        if (static_cast<int>(Entity->GetOwner()->GetInstanceID()->GetID()) == ExclusionID) continue;

        const Rectangle& EntityRect = Entity->GetCollidable();
        const std::vector<std::pair<Vector2, Vector2>> RectangleLines = MakeLinesFromRectangle(EntityRect);

        Vector2 CollisionPoint{};
        for (const auto& [Left, Right] : RectangleLines)
        {
            CheckCollisionLines(Line.first, Line.second, Left, Right, &CollisionPoint);
            if (!Vector2Equals(CollisionPoint, Vector2Zero()))
            {
                CollidedPoints.emplace_back(CollisionPoint, Entity->GetOwner());
            }
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

RaycastResult Raycast::Cast(const Vector2& From, const Vector2& To, CollisionLayer Layer)
{
    RaycastResult Result;

    if (Vector2Equals(From, To))
    {
        return Result;
    }

    const Rectangle CollisionArea = BuildRectangle(From, To);

    const std::vector<std::shared_ptr<BoxColliderComponent>> Entities = Quadtree.Search(CollisionArea);
    if (Entities.empty())
    {
        return Result;
    }

    std::vector<std::pair<Vector2, Object*>> CollidedPoints;

    const std::pair<Vector2, Vector2> Line = std::make_pair(From, To);
    for (const auto& Entity : Entities)
    {
        if (Entity->GetLayer() == Layer) continue;

        const Rectangle& EntityRect = Entity->GetCollidable();
        const std::vector<std::pair<Vector2, Vector2>> RectangleLines = MakeLinesFromRectangle(EntityRect);

        Vector2 CollisionPoint{};
        for (const auto& [Left, Right] : RectangleLines)
        {
            CheckCollisionLines(Line.first, Line.second, Left, Right, &CollisionPoint);
            if (!Vector2Equals(CollisionPoint, Vector2Zero()))
            {
                CollidedPoints.emplace_back(CollisionPoint, Entity->GetOwner());
            }
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

    const Rectangle CollisionArea = BuildRectangle(From, To);

    const std::vector<std::shared_ptr<BoxColliderComponent>> Entities = Quadtree.Search(CollisionArea);
    if (Entities.empty())
    {
        return Result;
    }

    std::vector<std::pair<Vector2, Object*>> CollidedPoints;

    const std::pair<Vector2, Vector2> Line = std::make_pair(From, To);
    for (const auto& Entity : Entities)
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
        const std::vector<std::pair<Vector2, Vector2>> RectangleLines = MakeLinesFromRectangle(EntityRect);

        Vector2 CollisionPoint{};
        for (const auto& [Left, Right] : RectangleLines)
        {
            CheckCollisionLines(Line.first, Line.second, Left, Right, &CollisionPoint);
            if (!Vector2Equals(CollisionPoint, Vector2Zero()))
            {
                CollidedPoints.emplace_back(CollisionPoint, Entity->GetOwner());
            }
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
