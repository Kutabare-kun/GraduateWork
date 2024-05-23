#pragma once
#include "../GameOverWidget/GameOverWidget.h"

class GameWinWidget
    : public GameOverWidget
{
public:
    GameWinWidget(Object* Owner, const Slot& LayoutSlot, UIBase* Parent = nullptr);
};
