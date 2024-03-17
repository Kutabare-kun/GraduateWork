#include "Obstacle.h"

Obstacle::Obstacle(const std::string& TexturePath, Vector2 Posisiton)
    : Actor(TexturePath, Posisiton)
{
    bEnableTicks = false;
}

void Obstacle::BeginPlay()
{
}

void Obstacle::EventTick(float DeltaTime)
{
}

void Obstacle::EndPlay()
{
}

void Obstacle::Draw() const
{
    Actor::Draw();
}
