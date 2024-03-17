#pragma once
#include <raylib.h>
#include <string>

// Forward Declarations
class SmartTexture;

class SmartImage final
{
public:
    // Load image from file
    explicit SmartImage(const std::string& Path);

    // Load image from texture
    explicit SmartImage(Texture2D& SourceTexture);

    // Load image from texture
    explicit SmartImage(SmartTexture& SourceTexture);

    // Load image from memory buffer
    SmartImage(const std::string& FileType, const unsigned char* FileData, int DataSize);

    // Copy constructor
    SmartImage(const SmartImage& Other) = delete;
    SmartImage& operator=(const SmartImage& Other) = delete;

    // Move constructor
    SmartImage(SmartImage&& Other) = delete;
    SmartImage& operator=(SmartImage&& Other) = delete;

    // Destructor
    ~SmartImage();

    // Load image from file
    void LoadNewImage(const std::string& Path);

    // Load image from file
    void LoadNewImage(Texture2D& SourceTexture);

    // Load image from texture
    void LoadNewImage(SmartTexture& SourceTexture);

    // Load image from file
    void LoadNewImage(const std::string& FileType, const unsigned char* FileData, int DataSize);

    // Getters
    Image& GetImage();
    const Image& GetImage() const;

private:
    Image _Image;

    bool bIsLoaded = false;
};
