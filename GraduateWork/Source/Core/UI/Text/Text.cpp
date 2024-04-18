#include "Text.h"
#include <cmath>


Text::Text(Object* Owner, const Rectangle& Bounds, UIObject* Parent, Alignment HorizontalAlignment,
           TextSettings& TextAppearance)
    : UIObject(Owner, Bounds, Parent, HorizontalAlignment), TextAppearance(TextAppearance)
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
    
    while (GetTextWidth() > GetSize().x)
    {
        SetFontSize(TextAppearance.FontSize - 0.1f);
    }
}

void Text::Draw()
{   
    if (GetParent())
    {
        DrawTextPro(TextAppearance.TextFont, TextAppearance.InfoText.c_str(), GetParentRelativePosition(),
                    TextAppearance.Origin, TextAppearance.Rotation, TextAppearance.FontSize, TextAppearance.Spacing,
                    TextAppearance.Tint);
    }
    else
    {
        DrawTextPro(TextAppearance.TextFont, TextAppearance.InfoText.c_str(), GetRelativePosition(),
                    TextAppearance.Origin, TextAppearance.Rotation, TextAppearance.FontSize, TextAppearance.Spacing,
                    TextAppearance.Tint);
    }
}

int Text::GetTextWidth() const
{
    return MeasureText(TextAppearance.InfoText.c_str(),
                       std::lroundf(TextAppearance.TextFont.baseSize * TextAppearance.FontSize));
}
