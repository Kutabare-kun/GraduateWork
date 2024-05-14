#include "UIText.h"

UIText::UIText(Object* Owner, const Slot& LayoutSlot, UIBase* Parent, const TextSettings& TextAppearance)
    : UIBase(Owner, LayoutSlot, Parent), TextAppearance(TextAppearance)
{
}

void UIText::Awake()
{
    UIBase::Awake();
}

void UIText::Update(float DeltaTime)
{
    UIBase::Update(DeltaTime);
}

void UIText::Draw()
{
    UIBase::Draw();

    Rectangle Rect = GetBounds();
    Vector2 Position = {Rect.x + Rect.width / 2.0f, Rect.y + Rect.height / 2.0f};
    const Vector2 Measure = MeasureTextEx(TextAppearance.TextFont, TextAppearance.InfoText.c_str(),
                                          TextAppearance.FontSize, TextAppearance.Spacing);
    Position.x -= Measure.x / 2.0f;
    Position.y -= Measure.y / 2.0f;

    DrawTextPro(TextAppearance.TextFont, TextAppearance.InfoText.c_str(), Position, Vector2{0.0f, 0.0f},
                TextAppearance.Rotation, TextAppearance.FontSize, TextAppearance.Spacing, TextAppearance.Tint);
}
