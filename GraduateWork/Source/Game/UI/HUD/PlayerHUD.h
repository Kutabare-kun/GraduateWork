#pragma once
#include <memory>

#include "../../../Core/UI/HUD/BaseHUD.h"

class GameUI;

class PlayerHUD
    : public BaseHUD
{
public:
    PlayerHUD(Object* Owner);

    void Awake() override;

    void LateUpdate(float DeltaTime) override;

    void Draw(const Camera2D& OwnerCamera) override;

    std::shared_ptr<GameUI> GetGameUIWidget() const { return GameUIWidget; }

private:
    std::shared_ptr<GameUI> GameUIWidget;
};
