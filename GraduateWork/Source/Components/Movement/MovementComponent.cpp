#include "MovementComponent.h"

#include <array>

#include "../../Actors/Actor.h"
#include "../../World/World.h"

MovementComponent::MovementComponent(Actor* NewOwner)
{
    AttachTo(NewOwner);
}

MovementComponent::MovementComponent(Actor* NewOwner, float NewSpeed, float NewMaxSpeed)
    : Speed(NewSpeed),
      MaxSpeed(NewMaxSpeed)
{
    AttachTo(NewOwner);
}

void MovementComponent::AttachTo(Actor* NewOwner)
{
    Owner = NewOwner;
}

void MovementComponent::EventTick(float DeltaTime)
{
    if (!Owner) return;

    const Vector2 ActorPosition = Owner->GetActorPosition();
    const Rectangle ActorRectangle = Owner->GetActorRectangle();

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
            float LeftA = NewRectangle.x;
            float RightA = NewRectangle.x + NewRectangle.width;
            float TopA = NewRectangle.y;
            float BottomA = NewRectangle.y + NewRectangle.height;

            // Calculate wall's AABB edges
            float LeftB = ObstacleRectangle.x;
            float RightB = ObstacleRectangle.x + ObstacleRectangle.width;
            float TopB = ObstacleRectangle.y;
            float BottomB = ObstacleRectangle.y + ObstacleRectangle.height;

            // Calculate penetration distance for each axis
            std::array<float, 4> Penetrations{RightA - LeftB, RightB - LeftA, BottomA - TopB, BottomB - TopA};

            // Find the axis with the smallest penetration
            auto MinPenetrationIt = std::min_element(Penetrations.begin(), Penetrations.end());
            float MinPenetration = *MinPenetrationIt;
            size_t MinIndex = std::distance(Penetrations.begin(), MinPenetrationIt);

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

    Owner->SetActorPosition(NewPosition);

    Velocity = {};
}

void MovementComponent::InputValue(float Value, const Vector2& Direction)
{
    Velocity.x += Value * Speed * Direction.x;
    Velocity.y += Value * Speed * Direction.y;
}
