#pragma once
#include "../../../Core/Object/Actor/Actor.h"
#include "../../UI/HUD/PlayerHUD/PlayerHUD.h"


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
    
    std::shared_ptr<PlayerHUD> GetHUD() const { return ContentHUD; }

protected:
    std::shared_ptr<MovementComponent> MovementComp;
    std::shared_ptr<CameraComponent> CameraComp;

private:
    void CreateAnimation();

    std::shared_ptr<PlayerHUD> ContentHUD;
};
