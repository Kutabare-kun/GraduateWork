#pragma once
#include "../../Core/Object/Actor/Actor.h"

class Player;

class PowerUpBase
    : public Actor
{
public:
    PowerUpBase(SharedContext* Context, Object* Instigator, const Vector2& Position);

    void Awake() override;

    void OnCollisionBeginOverlap(std::shared_ptr<ColliderComponent> Other) override;

protected:
    virtual void OnTakePowerUp(Player* ThisPlayer) = 0;

    float TimeToRemove = 20.0f;
};
