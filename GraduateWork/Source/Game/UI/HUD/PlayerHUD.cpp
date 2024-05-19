#include "PlayerHUD.h"

PlayerHUD::PlayerHUD(Object* Owner)
    : BaseHUD(Owner)
{
}

void PlayerHUD::Awake()
{
    std::shared_ptr<TestWidget> Widget = std::make_shared<TestWidget>(GetOwner(), Slot{Padding{0.0f}, Rectangle{0.0f, 0.0f, 200.0f, 80.0f}}, nullptr);
    auto Child = std::dynamic_pointer_cast<UIBase>(Widget);
    UIElements.push_back(Child);
    
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
