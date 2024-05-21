#pragma once
#include <string>
#include <filesystem>

#include "../Pattern/Singleton.h"

class Directory final
    : public Singleton<Directory>
{
public:
    std::string GetResource(const std::string&& ResourceName) const { return ResourcePath + R"(\)" + ResourceName; }
    std::string GetTexture(const std::string&& TextureName) const { return TexturePath + R"(\)" + TextureName; }
    std::string GetMap(const std::string&& MapName) const { return MapPath + R"(\)" + MapName; }
    std::string GetTileSet(const std::string&& TileSetName) const { return TileSetPath + R"(\)" + TileSetName; }
    std::string GetFont(const std::string&& FontName) const { return FontPath + R"(\)" + FontName; }
    std::string GetData(const std::string&& DataName) const { return DataPath + R"(\)" + DataName; }

    std::string GetCurrentPath() const { return CurrentPath; }

private:
    const std::string CurrentPath = std::filesystem::current_path().string().erase(std::filesystem::current_path().string().find_last_of('\\'));
    const std::string ResourcePath = CurrentPath + R"(\Resource)";

    const std::string FontPath = ResourcePath + R"(\Font)";
    const std::string TexturePath = ResourcePath + R"(\Texture)";
    const std::string MapPath = ResourcePath + R"(\Maps)";
    const std::string TileSetPath = ResourcePath + R"(\TileSet)";
    const std::string DataPath = ResourcePath + R"(\Data)";
};
