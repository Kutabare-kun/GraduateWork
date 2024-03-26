#pragma once

#include <raylib.h>
#include <unordered_map>
#include <vector>

#include "../../Allocator/ResourceAllocator.h"
#include "../XML/rapidxml.hpp"

class Object;
class TextureResource;

struct TileInfo
{
    TileInfo() : TileID(-1), TextureID(-1)
    {
    }

    TileInfo(int NewTileID, int NewTextureID, const Rectangle& NewTextureRect)
        : TileID(NewTileID), TextureID(NewTextureID), TextureRect(NewTextureRect)
    {
    }

    int TileID;
    int TextureID;
    Rectangle TextureRect;
};

struct Tile
{
    std::shared_ptr<TileInfo> Properties;
    Vector2 Position;
};

struct TileSheetData
{
    int TextureID;
    Vector2 ImageSize;
    Vector2 TileSize;
    int Columns;
    int Rows;
};

using Layer = std::vector<std::shared_ptr<Tile>>;
using MapTiles = std::map<std::string, std::shared_ptr<Layer>>;
using TileSet = std::unordered_map<unsigned, std::shared_ptr<TileInfo>>;

using namespace rapidxml;

class TileMapParser
{
public:
    TileMapParser(ResourceAllocator<TextureResource>& NewTextureAllocator);

    std::vector<std::shared_ptr<Object>> Parse(const std::string& FilePath, const Vector2& Offset);

private:
    std::shared_ptr<TileSheetData> BuildTileSheetData(xml_node<>* RootNode);
    std::shared_ptr<MapTiles> BuildMapTiles(xml_node<>* RootNode);
    std::pair<std::string, std::shared_ptr<Layer>> BuildLayer(xml_node<>* LayerNode, const std::shared_ptr<TileSheetData>& TileSheet);

    ResourceAllocator<TextureResource>& TextureAllocator;
};
