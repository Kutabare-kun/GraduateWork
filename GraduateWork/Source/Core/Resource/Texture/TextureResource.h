#pragma once
#include <raylib.h>

#include "../Base/BaseResource.h"

class TextureResource
    : public BaseResource<TextureResource, Texture2D>
{
public:
    ~TextureResource() override;
    
    bool LoadFromFile(const std::string& FilePath) override;

    Texture2D& Get_Impl();

private:
    Texture2D Sprite;
};
