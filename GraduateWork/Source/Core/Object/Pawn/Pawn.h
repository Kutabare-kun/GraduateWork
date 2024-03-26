#pragma once
#include "../Actor/Actor.h"

class MovementComponent;

class Pawn
    : public Actor
{
public:
    Pawn(const std::string& TexturePath, Vector2 Position);

    ~Pawn() override = default;
    
    void Awake() override;
    
    void Update(float DeltaTime) override;
    void LateUpdate(float DeltaTime) override;

    void Draw() override;

protected:
    std::shared_ptr<MovementComponent> MovementComp;
};
