#pragma once
#include <string>
#include "raylib.h"

// Forward Declarations
class SmartImage;

class SmartTexture final
{
public:
    // Load texture from file
    explicit SmartTexture(const std::string& Path);

    // Load texture from image
    explicit SmartTexture(Image& SourceImage);

    // Load texture from image
    explicit SmartTexture(SmartImage& SourceImage);

    // Copy constructor
    SmartTexture(const SmartTexture& Other) = delete;
    SmartTexture& operator=(const SmartTexture& Other) = delete;

    // Move constructor
    SmartTexture(SmartTexture&& Other) = delete;
    SmartTexture& operator=(SmartTexture&& Other) = delete;

    // Destructor
    ~SmartTexture();

    // Load texture from file
    void LoadNewTexture(const std::string& Path);

    // Load texture from image
    void LoadNewTexture(Image& SourceImage);

    // Load texture from image
    void LoadNewTexture(SmartImage& SourceImage);

    void DrawTexture(const Vector2& Position) const;
    
    // Getters
    Texture2D& GetTexture();
    const Texture2D& GetTexture() const;

    // Get texture rectangle, without Position in World
    Rectangle GetTextureRectangle() const;

    float GetScale() const;

    Color GetTint() const;

    // Setters
    void SetScale(const float& NewScale = 1.0f);

    void SetTint(const Color& NewTint = WHITE);

protected:
    float Scale = 1.0f;

    Color Tint = WHITE;

private:
    Texture2D _Texture;

    bool _bIsLoaded = false;
};
