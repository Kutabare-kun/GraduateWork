#include "FontResource.h"

FontResource::~FontResource()
{
    UnloadFont(TextFont);
}

bool FontResource::LoadFromFile(const std::string& FilePath)
{
    TextFont = LoadFont(FilePath.c_str());

    return true;
}

Font FontResource::Get_Impl()
{
    return TextFont;
}
