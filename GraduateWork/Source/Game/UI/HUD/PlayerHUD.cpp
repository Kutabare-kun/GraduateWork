#include "PlayerHUD.h"

#include "../Widgets/GameUI/GameUI.h"

PlayerHUD::PlayerHUD(Object* Owner)
    : BaseHUD(Owner)
{
}

void PlayerHUD::Awake()
{
    GameUIWidget = std::make_shared<GameUI>(
        GetOwner(), Slot{Padding{0.0f}, Crop{0.0f}, Rectangle{0.0f, 0.0f, 200.0f, 80.0f}}, nullptr);
    AddUIElement(GameUIWidget);

    BaseHUD::Awake();
}

void PlayerHUD::LateUpdate(float DeltaTime)
{
    BaseHUD::LateUpdate(DeltaTime);
}

void PlayerHUD::Draw(const Camera2D& OwnerCamera)
{
    BaseHUD::Draw(OwnerCamera);
}
