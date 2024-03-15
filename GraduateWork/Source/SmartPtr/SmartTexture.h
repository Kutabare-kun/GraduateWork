#pragma once
#include <string>
#include "raylib.h"

// Forward Declarations
class SmartImage;

class SmartTexture final
{
public:
    // Load texture from file
    SmartTexture(const std::string& Path);

    // Load texture from image
    SmartTexture(Image& SourceImage);

    // Load texture from image
    SmartTexture(SmartImage& SourceImage);

    ~SmartTexture();

    // Load texture from file
    void LoadNewTexture(const std::string& Path);

    // Load texture from image
    void LoadNewTexture(Image& SourceImage);

    // Load texture from image
    void LoadNewTexture(SmartImage& SourceImage);

    Texture2D& GetTexture();
    const Texture2D& GetTexture() const;

private:
    Texture2D _Texture;
};
