#include "SmartTexture.h"

#include "SmartImage.h"

SmartTexture::SmartTexture(const std::string& Path)
{
    LoadNewTexture(Path);   
}

SmartTexture::SmartTexture(Image& SourceImage)
{
    LoadNewTexture(SourceImage);
}

SmartTexture::SmartTexture(SmartImage& SourceImage)
{
    LoadNewTexture(SourceImage);
}

SmartTexture::~SmartTexture()
{
    UnloadTexture(_Texture);
}

void SmartTexture::LoadNewTexture(const std::string& Path)
{
    UnloadTexture(_Texture);
    
    _Texture = LoadTexture(Path.c_str());
}

void SmartTexture::LoadNewTexture(Image& SourceImage)
{
    UnloadTexture(_Texture);

    _Texture = LoadTextureFromImage(SourceImage);
}

void SmartTexture::LoadNewTexture(SmartImage& SourceImage)
{
    UnloadTexture(_Texture);

    LoadNewTexture(SourceImage.GetImage());
}

Texture2D& SmartTexture::GetTexture()
{
    return _Texture;
}

const Texture2D& SmartTexture::GetTexture() const
{
    return _Texture;
}


