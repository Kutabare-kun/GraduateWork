#pragma once
#include "../../../../Core/UI/UIBase/UIBase.h"

class LevelBorder
    : public UIBase
{
public:
    LevelBorder(Object* Owner, const Slot& LayoutSlot, UIBase* Parent);

    void Awake() override;

    void UpdateLevel() const;

private:
    std::shared_ptr<UIText> LevelText;
};
