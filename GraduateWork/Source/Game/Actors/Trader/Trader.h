#pragma once
#include "../../../Core/Object/Actor/Actor.h"

class Trader
    : public Actor
{
public:
    Trader(SharedContext* Context, Object* Instigator, const Vector2& Position = {0.0f, 0.0f });
    ~Trader() override = default;

    void Awake() override;

    void Update(float DeltaTime) override;
    void LateUpdate(float DeltaTime) override;

    void Draw(const Camera2D& OwnerCamera) override;

    void OnHealthChange(Object* Instigator, float Delta, bool IsDead) override;

protected:
    void CreateAnimation() override;
};
