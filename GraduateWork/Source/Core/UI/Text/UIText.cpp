#include "UIText.h"

UIText::UIText(Object* Owner, const Slot& LayoutSlot, UIBase* Parent, const TextSettings& TextAppearance)
    : UIBase(Owner, LayoutSlot, Parent), TextAppearance(TextAppearance)
{
    SetName(TextFormat("Text %s", TextAppearance.InfoText.c_str()));
}

void UIText::Draw()
{
    UIBase::Draw();

    if (!IsVisible()) return;

    const Slot& TextLayout = GetLayoutSlot();
    Rectangle Rect = GetBounds();
    Vector2 Position = {Rect.x + Rect.width / 2.0f, Rect.y + Rect.height / 2.0f};
    const Vector2 Measure = MeasureTextEx(TextAppearance.TextFont, TextAppearance.InfoText.c_str(),
                                          TextAppearance.FontSize, TextAppearance.Spacing);

    Position.x -= Measure.x / 2.0f;
    Position.y -= Measure.y / 2.0f;

    Position.x += TextLayout.ObjectPadding.Left - TextLayout.ObjectPadding.Right;
    Position.y += TextLayout.ObjectPadding.Top - TextLayout.ObjectPadding.Bottom;

    DrawTextPro(TextAppearance.TextFont, TextAppearance.InfoText.c_str(), Position, Vector2{0.0f, 0.0f},
                TextAppearance.Rotation, TextAppearance.FontSize, TextAppearance.Spacing, TextAppearance.Tint);
}
