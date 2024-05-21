#pragma once
#include "../UIBase/UIBase.h"

struct TextSettings
{
    TextSettings(const Font& TextFont, const std::string& InfoText, const Vector2& Origin, float Rotation = 0.0f,
                 float FontSize = 14.0f, float Spacing = 1.0f, const Color& Tint = WHITE)
        : TextFont(TextFont), InfoText(InfoText), Origin(Origin), Rotation(Rotation), FontSize(FontSize), Spacing(Spacing),
          Tint(Tint)
    {
    }
    Font TextFont;
    std::string InfoText;
    Vector2 Origin;
    float Rotation;
    float FontSize;
    float Spacing;
    Color Tint;
};

class UIText
    : public UIBase
{
public:
    UIText(Object* Owner, const Slot& LayoutSlot, UIBase* Parent, const TextSettings& TextAppearance);

    void Draw() override;

private:
    TextSettings TextAppearance;
};
