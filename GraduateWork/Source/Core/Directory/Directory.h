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
    
    std::string GetCurrentPath() const { return CurrentPath; }
    
private:
    std::string CurrentPath = std::filesystem::current_path().string().erase(std::filesystem::current_path().string().find_last_of('\\'));
    std::string ResourcePath = CurrentPath + R"(\Resource)";
    
    std::string TexturePath = ResourcePath + R"(\Texture)";
    std::string MapPath = ResourcePath + R"(\Maps)";
};
