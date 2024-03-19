#include "Player.h"

#include "../../World/World.h"

Player::Player(const std::string& TexturePath, Vector2 Posisiton)
    : Actor(TexturePath, Posisiton)
{
    MovementComp = std::make_unique<MovementComponent>(this);
    MovementComp->SetSpeed(400.0f);
    MovementComp->SetMaxSpeed(400.0f);

    CameraComp = std::make_unique<CameraComponent>(GetActorPosition());
    CameraComp->AttachTo(this);
    CameraComp->UpdateZoom(1.0f);
}

void Player::BeginPlay()
{
}

void Player::EventTick(float DeltaTime)
{
    // Movement
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

    MovementComp->EventTick(DeltaTime);
    // ~Movement

    // Camera
    CameraComp->UpdateCamera();
    // ~Camera
}

void Player::EndPlay()
{
}

void Player::Draw() const
{
    Actor::Draw();
}
