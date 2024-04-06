#include "Pawn.h"
#include "../../Component/Movement/MovementComponent.h"

Pawn::Pawn(SharedContext* Context, const Vector2& Position, float Speed)
    : Actor(Context, Position)
{
    MovementComp = AddComponent<MovementComponent>(this, Speed);
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
