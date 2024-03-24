#include "Player.h"

#include "../../World/World.h"

Player::Player(const std::string& TexturePath, Vector2 Posisiton)
    : Actor(TexturePath, Posisiton)
{}

void Player::BeginPlay()
{
    MovementComp = AddComponent<MovementComponent>(this);
    MovementComp->SetSpeed(400.0f);

    CameraComp = AddComponent<CameraComponent>(this, GetActorPosition());
    CameraComp->UpdateZoom(1.0f);
}

void Player::Move(float DeltaTime)
{
    // Movement Input
    if (IsKeyDown(KEY_W))
    {
        MovementComp->InputValue(-1.0f, Vector2{0.0f, 1.0f});
    }

    if (IsKeyDown(KEY_S))
    {
        MovementComp->InputValue(1.0f, Vector2{0.0f, 1.0f});
    }

    if (IsKeyDown(KEY_A))
    {
        MovementComp->InputValue(-1.0f, Vector2{1.0f, 0.0f});
    }

    if (IsKeyDown(KEY_D))
    {
        MovementComp->InputValue(1.0f, Vector2{1.0f, 0.0f});
    }
    // ~Movement Input
}

void Player::EventTick(float DeltaTime)
{
    // Movement
    Move(DeltaTime);
    // ~Movement

    for (auto& Component : GetAllComponents())
    {
        Component->EventTick(DeltaTime);
    }
}

void Player::EndPlay()
{
}

void Player::Draw() const
{
    Actor::Draw();
}
