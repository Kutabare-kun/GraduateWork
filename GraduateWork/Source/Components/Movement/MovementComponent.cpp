#include "MovementComponent.h"

#include <array>
#include <iostream>
#include <raymath.h>

#include "../../Actors/Actor.h"
#include "../../World/World.h"

MovementComponent::MovementComponent(Actor* NewOwner)
    : ActorComponent(NewOwner, true)
{
}

MovementComponent::MovementComponent(Actor* NewOwner, float NewSpeed)
    : ActorComponent(NewOwner, true),
    Speed(NewSpeed)
{
}

void MovementComponent::EventTick(float DeltaTime)
{
    if (!GetOwner()) return;

    const Vector2 ActorPosition = GetOwner()->GetActorPosition();
    const Rectangle ActorRectangle = GetOwner()->GetActorRectangle();
    
    // Collision detection
    Vector2 NewPosition = {ActorPosition.x + Velocity.x * DeltaTime, ActorPosition.y + Velocity.y * DeltaTime};

    for (auto Iter = World::GetInstance().GetObstacles().cbegin(); Iter != World::GetInstance().GetObstacles().cend();
         ++Iter)
    {
        const Actor* Obstacle = Iter->get();
        const Rectangle ObstacleRectangle = Obstacle->GetActorRectangle();
        const Rectangle NewRectangle = {NewPosition.x, NewPosition.y, ActorRectangle.width, ActorRectangle.height};
        
        // Check for collision
        if (CheckCollisionRecs(NewRectangle, ObstacleRectangle))
        {
            // Calculate player's AABB edges
            const float LeftA = NewRectangle.x;
            const float RightA = NewRectangle.x + NewRectangle.width;
            const float TopA = NewRectangle.y;
            const float BottomA = NewRectangle.y + NewRectangle.height;

            // Calculate wall's AABB edges
            const float LeftB = ObstacleRectangle.x;
            const float RightB = ObstacleRectangle.x + ObstacleRectangle.width;
            const float TopB = ObstacleRectangle.y;
            const float BottomB = ObstacleRectangle.y + ObstacleRectangle.height;

            // Calculate penetration distance for each axis
            const std::array<float, 4> Penetrations{RightA - LeftB, RightB - LeftA, BottomA - TopB, BottomB - TopA};

            // Find the axis with the smallest penetration
            const auto MinPenetrationIt = std::min_element(Penetrations.begin(), Penetrations.end());
            const float MinPenetration = *MinPenetrationIt;
            const size_t MinIndex = std::distance(Penetrations.begin(), MinPenetrationIt);

            // Resolve collision based on the axis with the smallest penetration
            switch (MinIndex)
            {
            case 0:
                // Left penetration
                NewPosition.x -= MinPenetration;
                break;
            case 1:
                // Right penetration
                NewPosition.x += MinPenetration;
                break;
            case 2:
                // Top penetration
                NewPosition.y -= MinPenetration;
                break;
            case 3:
                // Bottom penetration
                NewPosition.y += MinPenetration;
                break;
            }

            Iter = World::GetInstance().GetObstacles().cbegin();
        }
    }
    // ~Collision detection

    GetOwner()->SetActorPosition(NewPosition);

    Velocity = {};
}

void MovementComponent::InputValue(float Value, const Vector2& Direction)
{
    Velocity.x += Value * Speed * Direction.x;
    Velocity.y += Value * Speed * Direction.y;

    MovementDirection = Vector2Normalize(Velocity);
}
