#pragma once

#include <raylib.h>
#include <unordered_map>
#include <vector>

#include "../../Allocator/ResourceAllocator.h"
#include "../../Context/SharedContext/SharedContext.h"
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

struct Layer
{
    std::vector<std::shared_ptr<Tile>> Tiles;
    bool bIsVisible;
};

using MapTiles = std::vector<std::pair<std::string, std::shared_ptr<Layer>>>;
using TileSet = std::unordered_map<unsigned, std::shared_ptr<TileInfo>>;
using TileSheets = std::map<int, std::shared_ptr<TileSheetData>>;

using namespace rapidxml;

class TileMapParser
{
public:
    TileMapParser(ResourceAllocator<TextureResource>& NewTextureAllocator, SharedContext& Context);

    std::vector<std::shared_ptr<Object>> Parse(const std::string& FilePath, const Vector2& Offset);

private:
    std::shared_ptr<TileSheets> BuildTileSheetData(xml_node<>* RootNode);
    std::shared_ptr<MapTiles> BuildMapTiles(xml_node<>* RootNode);
    std::pair<std::string, std::shared_ptr<Layer>> BuildLayer(xml_node<>* LayerNode, const std::shared_ptr<TileSheets>& TileSheets);

    ResourceAllocator<TextureResource>& TextureAllocator;
    SharedContext& Context;
};
