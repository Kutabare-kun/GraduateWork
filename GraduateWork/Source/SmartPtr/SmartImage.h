#pragma once
#include <raylib.h>
#include <string>

// Forward Declarations
class SmartTexture;

class SmartImage final
{
public:
    // Load image from file
    SmartImage(const std::string& Path);

    // Load image from texture
    SmartImage(Texture2D& SourceTexture);

    // Load image from texture
    SmartImage(SmartTexture& SourceTexture);

    // Load image from memory buffer
    SmartImage(const std::string& FileType, const unsigned char* FileData, int DataSize);

    ~SmartImage();

    // Load image from file
    void LoadNewImage(const std::string& Path);

    // Load image from file
    void LoadNewImage(Texture2D& SourceTexture);

    // Load image from texture
    void LoadNewImage(SmartTexture& SourceTexture);

    // Load image from file
    void LoadNewImage(const std::string& FileType, const unsigned char* FileData, int DataSize);

    Image& GetImage();
    const Image& GetImage() const;

private:
    Image _Image;
};
