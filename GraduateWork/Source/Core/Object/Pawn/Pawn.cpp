#include "Pawn.h"
#include "../../Component/Movement/MovementComponent.h"

Pawn::Pawn(const std::string& TexturePath, Vector2 Position)
    : Actor(TexturePath, Position)
{
    MovementComp = AddComponent<MovementComponent>(this, 100.0f);
}

void Pawn::Awake()
{
    Actor::Awake();
}

void Pawn::Update(float DeltaTime)
{
    Actor::Update(DeltaTime);
}

void Pawn::LateUpdate(float DeltaTime)
{
    Actor::LateUpdate(DeltaTime);
}

void Pawn::Draw()
{
    Actor::Draw();
}
