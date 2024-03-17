#include "SmartTexture.h"

#include "SmartImage.h"

SmartTexture::SmartTexture(const std::string& Path)
{
    LoadNewTexture(Path);
    _bIsLoaded = true;
}

SmartTexture::SmartTexture(Image& SourceImage)
{
    LoadNewTexture(SourceImage);
    _bIsLoaded = true;
}

SmartTexture::SmartTexture(SmartImage& SourceImage)
{
    LoadNewTexture(SourceImage);
    _bIsLoaded = true;
}

SmartTexture::~SmartTexture()
{
    UnloadTexture(_Texture);
}

void SmartTexture::LoadNewTexture(const std::string& Path)
{
    if (_bIsLoaded)
        UnloadTexture(_Texture);
    
    _Texture = LoadTexture(Path.c_str());
}

void SmartTexture::LoadNewTexture(Image& SourceImage)
{
    if (_bIsLoaded)
        UnloadTexture(_Texture);

    _Texture = LoadTextureFromImage(SourceImage);
}

void SmartTexture::LoadNewTexture(SmartImage& SourceImage)
{
    if (_bIsLoaded)
        UnloadTexture(_Texture);

    LoadNewTexture(SourceImage.GetImage());
}

void SmartTexture::DrawTexture(const Vector2& Position) const
{
    DrawTexturePro(_Texture,
        { 0, 0, (float)_Texture.width, (float)_Texture.height },
        { Position.x, Position.y, (float)_Texture.width * Scale, (float)_Texture.height * Scale },
        { ((float)_Texture.width * Scale) / 2, ((float)_Texture.height * Scale) / 2 },
        0,
        Tint);
}

Rectangle SmartTexture::GetTextureRectangle() const
{
    return Rectangle{0, 0, (float)_Texture.width * Scale, (float)_Texture.height * Scale};
}

float SmartTexture::GetScale() const
{
    return Scale;
}

Color SmartTexture::GetTint() const
{
    return Tint;
}

void SmartTexture::SetScale(const float& NewScale)
{
    Scale = NewScale;
}

void SmartTexture::SetTint(const Color& NewTint)
{
    Tint = NewTint;
}

Texture2D& SmartTexture::GetTexture()
{
    return _Texture;
}

const Texture2D& SmartTexture::GetTexture() const
{
    return _Texture;
}
