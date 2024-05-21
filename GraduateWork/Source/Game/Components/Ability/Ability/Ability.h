#pragma once

#include "../../../../Core/Object/Actor/Actor.h"

class Ability
    : public Actor
{
public:
    Ability(SharedContext* Context, Object* Instigator, const Vector2& Position, float Damage);

    void Awake() override;

    void OnCollisionBeginOverlap(std::shared_ptr<ColliderComponent> Other) override;
    void OnCollisionStayOverlap(std::shared_ptr<ColliderComponent> Other) override;

protected:
    void CreateAnimation() override;

    virtual void OnBeginHit(class Enemy* Target);
    virtual void OnEveryHit(class Enemy* Target);

    float Damage;
};
