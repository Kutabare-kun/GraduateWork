#include "GameWinWidget.h"

GameWinWidget::GameWinWidget(Object* Owner, const Slot& LayoutSlot, UIBase* Parent)
    : GameOverWidget(Owner, LayoutSlot, Parent)
{
    TextResult = "YOU WIN";
    TextResultColor = GREEN;
}
