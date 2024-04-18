#include "Text.h"
#include <cmath>


Text::Text(Object* Owner, const Rectangle& Bounds, UIObject* Parent, Alignment HorizontalAlignment,
           TextSettings& TextAppearance)
    : UIObject(Owner, Bounds, Parent, HorizontalAlignment), TextAppearance(TextAppearance), TextPadding()
{
}

Text::~Text()
{
    TextAppearance.Unload();
}

void Text::Awake()
{
    UIObject::Awake();
}

void Text::Update(float DeltaTime)
{
    UIObject::Update(DeltaTime);

    while (GetTextWidth() > GetRelativeSize().x)
    {
        SetFontSize(TextAppearance.FontSize - 0.1f);
    }
}

void Text::Draw()
{
    const float TextWidth = GetTextWidth();
    Vector2 TextPosition = GetParent() ? GetParentRelativePosition() : GetRelativePosition();
    Vector2 TextSize = GetParent() ? GetParentRelativeSize() : GetRelativeSize();

    switch (GetObjectAlignment())
    {
    case Alignment::Center:
        TextPosition.x -= TextWidth / 2.0f;
        break;
    case Alignment::Right:
        TextPosition.x += TextSize.x - TextWidth;
        break;
        default: break;
    }

    DrawTextPro(TextAppearance.TextFont, TextAppearance.InfoText.c_str(), TextPosition,
                TextAppearance.Origin, TextAppearance.Rotation, TextAppearance.FontSize, TextAppearance.Spacing,
                TextAppearance.Tint);
}

int Text::GetTextWidth() const
{
    return MeasureText(TextAppearance.InfoText.c_str(),
                       std::lroundf(TextAppearance.TextFont.baseSize * TextAppearance.FontSize));
}
