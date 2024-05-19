#pragma once
#include <memory>

#include "../../../Core/UI/HUD/BaseHUD.h"
#include "../Widgets/TestWidget.h"

class PlayerHUD
    : public BaseHUD
{
public:
    PlayerHUD(Object* Owner);

    void Awake() override;

    void LateUpdate(float DeltaTime) override;

    void Draw(const Camera2D& OwnerCamera) override;

private:
    std::shared_ptr<TestWidget> UITestWidget;
};
