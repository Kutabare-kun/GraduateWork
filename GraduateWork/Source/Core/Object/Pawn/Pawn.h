#pragma once
#include "../Actor/Actor.h"

class MovementComponent;

class Pawn
    : public Actor
{
public:
    explicit Pawn(const Vector2& Position = {0.0f, 0.0f }, float Speed = 100.0f);

    ~Pawn() override = default;
    
    void Awake() override;
    
    void Update(float DeltaTime) override;
    void LateUpdate(float DeltaTime) override;

    void Draw() override;

protected:
    std::shared_ptr<MovementComponent> MovementComp;
};
