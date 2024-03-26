#include "TextureResource.h"

TextureResource::~TextureResource()
{
    UnloadTexture(Sprite);
}

bool TextureResource::LoadFromFile(const std::string& FilePath)
{
    Sprite = LoadTexture(FilePath.c_str());

    return true;
}

Texture2D& TextureResource::Get_Impl()
{
    return Sprite;
}
