#pragma once
#include "../../../../Core/UI/UIBase/UIBase.h"

class GameOverWidget
    : public UIBase
{
public:
    GameOverWidget(Object* Owner, const Slot& LayoutSlot, UIBase* Parent = nullptr);

    void Awake() override;

protected:
    std::string TextResult;
    Color TextResultColor;
};
