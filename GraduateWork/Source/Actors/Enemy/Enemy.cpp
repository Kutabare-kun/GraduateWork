#include "Enemy.h"

#include <iostream>

#include "raymath.h"

#include "../../Algorithm/Pathfinding/Astar.h"
#include "../../Constructor/Constructor.h"
#include "../../World/World.h"


Enemy::Enemy(const std::string& TexturePath, Vector2 Posisiton)
    : Actor(TexturePath, Posisiton)
{}

void Enemy::BeginPlay()
{
    MovementComp = AddComponent<MovementComponent>(this);
    MovementComp->SetSpeed(150.0f);
}

void Enemy::Move(float DeltaTime)
{
    const Actor* Player = World::GetInstance().GetPlayer();
    const Rectangle PlayerRectangle = Player->GetActorRectangle();
    const Vector2 PlayerPosition = Vector2Add({PlayerRectangle.x, PlayerRectangle.y},
                                              Vector2{PlayerRectangle.width / 2.0f, PlayerRectangle.height / 2.0f});

    const Rectangle AIRectangle = GetActorRectangle();
    const Vector2 AIPosition = Vector2Add({AIRectangle.x, AIRectangle.y},
                                          Vector2{AIRectangle.width / 2.0f, AIRectangle.height / 2.0f});

    const std::pair<int, int> IndexAIPosition = Constructor::GetInstance().ConvertToPair(AIPosition, 64);
    const std::pair<int, int> IndexPlayerPosition = Constructor::GetInstance().ConvertToPair(PlayerPosition, 64);
    auto [Success, Path] = Astar::GetInstance().FindPath(World::GetInstance().GetMapGrid(), IndexAIPosition,
                                                         IndexPlayerPosition);
    
    MemoryPath = Path;
    
    if (Success)
    {
        Vector2 Direction;
        if (Path.size() > 1)
        {
            const Vector2 NewPostion = Constructor::GetInstance().ConvertToVector2(Path.at(0), 64);
            Direction = Vector2Subtract(NewPostion, AIPosition);
        }
        else
        {
            Direction = Vector2Subtract(PlayerPosition, AIPosition);
        }
        Direction = Vector2Normalize(Direction);
        MovementComp->InputValue(1.0f, Direction);
    }

    MovementComp->EventTick(DeltaTime);
}

void Enemy::EventTick(float DeltaTime)
{
    // Movement
    Move(DeltaTime);
    // ~Movement
}

void Enemy::EndPlay()
{
}

void Enemy::Draw() const
{
    Actor::Draw();

    const Rectangle Rect = GetActorRectangle();
    Vector2 OldPosition = {Rect.x + Rect.width / 2.0f, Rect.y + Rect.height / 2.0f};
    const Vector2 To = Vector2Add(Vector2Scale(MovementComp->GetDirection(), 40.0f), OldPosition);

    DrawLineEx(OldPosition, To, 8.0f, WHITE);
    
    if (MemoryPath.empty()) return;

    OldPosition = Constructor::GetInstance().ConvertToVector2(MemoryPath[0], 64);
    for (size_t Index = 1; Index < MemoryPath.size(); ++Index)
    {
        Vector2 NewPosition = Constructor::GetInstance().ConvertToVector2(MemoryPath[Index], 64);
        DrawLineEx(OldPosition,NewPosition, 4.0f, RED);
        OldPosition = NewPosition;
    }
}
