#pragma once
#include "../../../Core/Object/Actor/Actor.h"

class CameraComponent;
class MovementComponent;

class Player
    : public Actor
{
public:
    Player(SharedContext* Context, const Vector2& Position = {0.0f, 0.0f }, float Speed = 100.0f);
    ~Player() override;

    void Awake() override;

    void Update(float DeltaTime) override;
    void LateUpdate(float DeltaTime) override;

    void Draw() override;

    std::shared_ptr<MovementComponent> GetMovement() const { return MovementComp; }
    std::shared_ptr<CameraComponent> GetCamera() const { return CameraComp; }

protected:
    std::shared_ptr<MovementComponent> MovementComp;
    std::shared_ptr<CameraComponent> CameraComp;

private:
    void CreateAnimation();
};
