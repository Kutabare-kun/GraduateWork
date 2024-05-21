#pragma once
#include "../Ability.h"

class VelocityComponent;

class ShurikenAbility
    : public Ability
{
public:
    ShurikenAbility(SharedContext* Context, Object* Instigator, const Vector2& Position, float Damage);

    void Awake() override;

    void OnEveryHit(Enemy* Target) override;

    void CreateAnimation() override;

protected:
    std::shared_ptr<VelocityComponent> VelocityComp;

    float Speed = 400.0f;
};
