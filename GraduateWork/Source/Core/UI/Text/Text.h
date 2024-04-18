#pragma once
#include <string>

#include "raylib.h"
#include "../UIObject.h"

struct TextSettings
{
    TextSettings(const Font& TextFont, const std::string& InfoText, const Vector2& Origin, float Rotation = 0.0f,
                 float FontSize = 14.0f, float Spacing = 1.0f, const Color& Tint = WHITE)
        : TextFont(TextFont), InfoText(InfoText), Origin(Origin), Rotation(Rotation), FontSize(FontSize), Spacing(Spacing),
          Tint(Tint)
    {
    }

    void Unload() const { UnloadFont(TextFont); }
    
    Font TextFont;
    std::string InfoText;
    Vector2 Origin;
    float Rotation;
    float FontSize;
    float Spacing;
    Color Tint;
};

class Text
    : public UIObject
{
public:
    Text(Object* Owner, const Rectangle& Bounds, UIObject* Parent, Alignment HorizontalAlignment,
         TextSettings& TextAppearance);

    ~Text() override;

    void Awake() override;
    
    void Update(float DeltaTime) override;

    void Draw() override;

    int GetTextWidth() const;

    const Font& GetFont() const { return TextAppearance.TextFont; }
    const std::string& GetText() const { return TextAppearance.InfoText; }
    const Vector2& GetOrigin() const { return TextAppearance.Origin; }
    const Color& GetTint() const { return TextAppearance.Tint; }
    float GetRotation() const { return TextAppearance.Rotation; }
    float GetFontSize() const { return TextAppearance.FontSize; }
    float GetSpacing() const { return TextAppearance.Spacing; }

    void SetTextFont(const Font& NewTextFont) { TextAppearance.TextFont = NewTextFont; }
    void SetInfoText(const std::string& NewInfoText) { TextAppearance.InfoText = NewInfoText; }
    void SetOrigin(const Vector2& NewOrigin) { TextAppearance.Origin = NewOrigin; }
    void SetRotation(float NewRotation) { TextAppearance.Rotation = NewRotation; }
    void SetFontSize(float NewFontSize) { TextAppearance.FontSize = NewFontSize; }
    void SetSpacing(float NewSpacing) { TextAppearance.Spacing = NewSpacing; }
    void SetTint(const Color& NewTint) { TextAppearance.Tint = NewTint; }

private:
    TextSettings TextAppearance;
};
