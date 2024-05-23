#pragma once
#include "../../../../Core/UI/UIBase/UIBase.h"

class MainWidgetScreen
    : public UIBase
{
public:
    MainWidgetScreen(Object* Owner, const Slot& LayoutSlot, UIBase* Parent);

    void Awake() override;

    void Update(float DeltaTime) override;

    void Draw() override;
};
