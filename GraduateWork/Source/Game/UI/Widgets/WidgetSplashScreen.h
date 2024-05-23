#pragma once
#include "../../../Core/UI/Panel/UIPanel.h"

class WidgetSplashScreen
    : public UIPanel
{
public:
    WidgetSplashScreen(Object* Owner, const Slot& LayoutSlot, UIBase* Parent);

    void Awake() override;

    void Update(float DeltaTime) override;

    void Draw() override;
};
