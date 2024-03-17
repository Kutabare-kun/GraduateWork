#include "SmartImage.h"
#include "SmartTexture.h"

SmartImage::SmartImage(const std::string& Path)
{
    LoadNewImage(Path);
    bIsLoaded = true;
}

SmartImage::SmartImage(Texture2D& SourceTexture)
{
    LoadNewImage(SourceTexture);
    bIsLoaded = true;
}

SmartImage::SmartImage(SmartTexture& SourceTexture)
{
    LoadNewImage(SourceTexture);
    bIsLoaded = true;
}

SmartImage::SmartImage(const std::string& FileType, const unsigned char* FileData, int DataSize)
{
    LoadNewImage(FileType, FileData, DataSize);
    bIsLoaded = true;
}

SmartImage::~SmartImage()
{
    UnloadImage(_Image);
}

void SmartImage::LoadNewImage(const std::string& Path)
{
    if (bIsLoaded)
        UnloadImage(_Image);
    
    _Image = LoadImage(Path.c_str());
}

void SmartImage::LoadNewImage(Texture2D& SourceTexture)
{
    if (bIsLoaded)
        UnloadImage(_Image);

    _Image = LoadImageFromTexture(SourceTexture);
}

void SmartImage::LoadNewImage(SmartTexture& SourceTexture)
{
    LoadNewImage(SourceTexture.GetTexture());
}

void SmartImage::LoadNewImage(const std::string& FileType, const unsigned char* FileData, int DataSize)
{
    if (bIsLoaded)
        UnloadImage(_Image);

    _Image = LoadImageFromMemory(FileType.c_str(), FileData, DataSize);
}

Image& SmartImage::GetImage()
{
    return _Image;
}

const Image& SmartImage::GetImage() const
{
    return _Image;
}
