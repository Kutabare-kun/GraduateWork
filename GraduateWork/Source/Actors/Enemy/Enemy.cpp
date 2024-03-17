#include "Enemy.h"

#include "../../World/World.h"

Enemy::Enemy(const std::string& TexturePath, Vector2 Posisiton)
    : Actor(TexturePath, Posisiton)
{
    MovementComp = std::make_unique<MovementComponent>(this);
    MovementComp->SetSpeed(150.0f);
    MovementComp->SetMaxSpeed(150.0f);
}

void Enemy::BeginPlay()
{
}

void Enemy::EventTick(float DeltaTime)
{
    // Movement
    MovementComp->EventTick(DeltaTime);
    // ~Movement
}

void Enemy::EndPlay()
{
}

void Enemy::Draw() const
{
    Actor::Draw();
}
