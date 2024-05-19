#pragma once
#include "../../../Core/Object/Actor/Actor.h"

class Trader
    : public Actor
{
public:
    Trader(SharedContext* Context, const Vector2& Position = {0.0f, 0.0f });
    ~Trader() override = default;

    void Awake() override;

    void Update(float DeltaTime) override;
    void LateUpdate(float DeltaTime) override;

    void Draw(const Camera2D& OwnerCamera) override;

protected:
    void CreateAnimation() override;
};
