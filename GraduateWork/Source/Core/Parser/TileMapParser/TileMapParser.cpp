#include "TileMapParser.h"

#include <iostream>
#include <sstream>

#include "../../Component/Collider/BoxCollider/BoxColliderComponent.h"
#include "../XML/rapidxml_utils.hpp"
#include "../../Component/Sprite/SpriteComponent.h"
#include "../../Directory/Directory.h"
#include "../../Object/Object.h"
#include "../../StaticFunctions/Debug.h"
#include "../../Utilities/Utilities.h"

TileMapParser::TileMapParser(ResourceAllocator<TextureResource>& NewTextureAllocator, SharedContext& Context)
    : TextureAllocator(NewTextureAllocator), Context(Context)
{
}

std::vector<std::shared_ptr<Object>> TileMapParser::Parse(const std::string& FilePath, const Vector2& Offset)
{
    char* FileLocation = new char[FilePath.size() + 1];
    strcpy_s(FileLocation, FilePath.size() + 1, FilePath.c_str());

    file<> XmlFile(FileLocation);
    xml_document<> Doc;
    Doc.parse<0>(XmlFile.data());
    xml_node<>* RootNode = Doc.first_node("map");

    const std::shared_ptr<MapTiles> Tiles = BuildMapTiles(RootNode);

    const int TileSizeX = std::atoi(RootNode->first_attribute("tilewidth")->value());
    const int TileSizeY = std::atoi(RootNode->first_attribute("tileheight")->value());

    std::vector<std::shared_ptr<Object>> TileObjects;

    constexpr int TextureID{ 1 };
    int LayerCount = static_cast<int>(Tiles->size()) - 1;

    constexpr int TileScale{4};

    Context.MaxTileSize = TileSizeX * TileScale;

    for (const auto& TileLayer : *Tiles)
    {
        for (const auto& TileProperties : TileLayer.second->Tiles)
        {
            std::shared_ptr<TileInfo> TileInfoObj = TileProperties->Properties;
            std::shared_ptr<Object> TileObject = std::make_shared<Object>(&Context, nullptr);

            if (TileLayer.second->bIsVisible)
            {
                auto Sprite = TileObject->AddComponent<SpriteComponent>(TileObject.get());
                Sprite->Load(TextureID);
                Sprite->SetTextureRect(TileInfoObj->TextureRect);
                Sprite->SetSortOrder(LayerCount);
                Sprite->SetDrawLayer(DrawLayer::Background);
            }

            const auto TransformComp = TileObject->GetTransform();
            TransformComp->SetScale({TileScale, TileScale});
            const Vector2 Position = {
                TileProperties->Position.x * static_cast<float>(TileSizeX) * TileScale + Offset.x,
                TileProperties->Position.y * static_cast<float>(TileSizeY) * TileScale + Offset.y
            };
            TransformComp->SetPosition(Position);
            TransformComp->SetStatic(true);

            if (TileLayer.first == "Collision")
            {
                auto BoxColliderComp = TileObject->AddComponent<BoxColliderComponent>(TileObject.get());
                BoxColliderComp->SetCollidable({
                    Position.x - TileSizeX * TileScale / 2.0f,
                    Position.y - TileSizeY * TileScale / 2.0f,
                    static_cast<float>(TileSizeX * TileScale),
                    static_cast<float>(TileSizeY * TileScale)
                });
                BoxColliderComp->SetLayer(CollisionLayer::Tile);
            }

            if (TileLayer.first == "Ceil")
            {
                auto Sprite = TileObject->AddComponent<SpriteComponent>(TileObject.get());
                Sprite->SetDrawLayer(DrawLayer::Foreground);
            }

            TileObjects.emplace_back(TileObject);
        }

        --LayerCount;
    }

    return TileObjects;
}

std::shared_ptr<TileSheets> TileMapParser::BuildTileSheetData(xml_node<>* RootNode)
{
    TileSheets TileSheetsData;

    for (xml_node<>* TileSheetLocation = RootNode->first_node("tileset"); TileSheetLocation;
         TileSheetLocation = TileSheetLocation->next_sibling("tileset"))
    {
        TileSheetData TileSheetDataObj;

        const int FirstID = std::atoi(TileSheetLocation->first_attribute("firstgid")->value());

        std::string FileTileSheet = TileSheetLocation->first_attribute("source")->value();
        FileTileSheet = Directory::GetInstance().GetTileSet(std::move(FileTileSheet));

        char* FileLocation = new char[FileTileSheet.size() + 1];
        strcpy_s(FileLocation, FileTileSheet.size() + 1, FileTileSheet.c_str());

        file<> XmlFile(FileLocation);
        xml_document<> Doc;
        Doc.parse<0>(XmlFile.data());

        xml_node<>* TileSheetNode = Doc.first_node("tileset");

        TileSheetDataObj.TileSize.x = static_cast<float>(
            std::atoi(TileSheetNode->first_attribute("tilewidth")->value()));
        TileSheetDataObj.TileSize.y = static_cast<float>(std::atoi(
            TileSheetNode->first_attribute("tileheight")->value()));

        const int TileCount = std::atoi(TileSheetNode->first_attribute("tilecount")->value());
        TileSheetDataObj.Columns = std::atoi(TileSheetNode->first_attribute("columns")->value());
        TileSheetDataObj.Rows = TileCount / TileSheetDataObj.Columns;

        xml_node<>* ImageNode = TileSheetNode->first_node("image");
        std::string ImageSource = ImageNode->first_attribute("source")->value();
        ImageSource = Directory::GetInstance().GetTileSet(std::move(ImageSource));
        TileSheetDataObj.TextureID = TextureAllocator.Add(ImageSource);

        TileSheetDataObj.ImageSize.x = static_cast<float>(std::atoi(ImageNode->first_attribute("width")->value()));
        TileSheetDataObj.ImageSize.y = static_cast<float>(std::atoi(ImageNode->first_attribute("height")->value()));

        TileSheetsData.insert(std::make_pair(FirstID, std::make_shared<TileSheetData>(TileSheetDataObj)));
    }

    return std::make_shared<TileSheets>(TileSheetsData);
}

std::shared_ptr<MapTiles> TileMapParser::BuildMapTiles(xml_node<>* RootNode)
{
    std::shared_ptr<TileSheets> TileSheetDataObj = BuildTileSheetData(RootNode);
    std::shared_ptr<MapTiles> Map = std::make_shared<MapTiles>();

    for (xml_node<>* Node = RootNode->first_node("layer"); Node; Node = Node->next_sibling())
    {
        std::pair<std::string, std::shared_ptr<Layer>> LayerPair = BuildLayer(Node, TileSheetDataObj);

        Map->emplace_back(LayerPair);
    }

    return Map;
}

std::pair<std::string, std::shared_ptr<Layer>> TileMapParser::BuildLayer(xml_node<>* LayerNode,
                                                                         const std::shared_ptr<TileSheets>& TileSheets)
{
    TileSet TileSetData;
    std::shared_ptr<Layer> LayerData = std::make_shared<Layer>();

    int Width = std::atoi(LayerNode->first_attribute("width")->value());
    std::string LayerName = LayerNode->first_attribute("name")->value();

    xml_node<>* DataNode = LayerNode->first_node("data");
    char* MapIndices = DataNode->value();

    std::stringstream FileStream(MapIndices);

    int Count = 0;

    if (LayerName == "Collision")
    {
        std::vector<std::vector<bool>> CollisionMap(Width, std::vector<bool>(Width, false));
        Context.CollisionMap = std::move(CollisionMap);
    }

    std::string Line;
    while (FileStream.good())
    {
        std::string Substr;
        std::getline(FileStream, Substr, ',');

        if (!Utilities::IsInteger(Substr))
        {
            // We remove special characters from the int before parsing
            std::erase(Substr, '\r');
            std::erase(Substr, '\n');

            //TODO: add additional check to 
            //confirm that the character removals have worked:
        }

        int TileId = std::stoi(Substr);

        if (LayerName == "Collision")
        {
            Context.CollisionMap[Count / Width][Count % Width] = TileId != 0;
        }

        if (TileId != 0)
        {
            auto Iter = TileSetData.find(TileId);
            if (Iter == TileSetData.end())
            {
                std::shared_ptr<TileSheetData> TileSheet;

                int FirstID = 0;

                for (auto& Sheet : *TileSheets)
                {
                    if (TileId >= Sheet.first)
                    {
                        FirstID = Sheet.first;
                        TileSheet = Sheet.second;
                        break;
                    }
                }

                if (!TileSheet)
                {
                    continue;
                }

                Vector2 TexturePosition{
                    static_cast<float>((TileId - FirstID) % TileSheet->Columns),
                    static_cast<float>((TileId - FirstID) / TileSheet->Columns)
                };

                std::shared_ptr<TileInfo> tileInfo =
                    std::make_shared<TileInfo>(
                        TileSheet->TextureID, TileId,
                        Rectangle(
                            TexturePosition.x * TileSheet->TileSize.x,
                            TexturePosition.y * TileSheet->TileSize.y,
                            TileSheet->TileSize.x,
                            TileSheet->TileSize.y)
                    );

                Iter = TileSetData.insert(std::make_pair(TileId, tileInfo)).first;
            }

            std::shared_ptr<Tile> TileData = std::make_shared<Tile>();

            // Bind properties of a tile from a set.
            TileData->Properties = Iter->second;
            TileData->Position = Vector2{
                static_cast<float>(Count % Width - 1),
                static_cast<float>(Count / Width)
            };

            LayerData->Tiles.emplace_back(TileData);
        }

        Count++;
    }

    const std::string layerName = LayerNode->first_attribute("name")->value();

    bool bIsLayerVisible = true;
    xml_attribute<>* VisibleAttribute = LayerNode->first_attribute("visible");
    if (VisibleAttribute)
    {
        bIsLayerVisible = std::atoi(VisibleAttribute->value()) == 1;
    }
    LayerData->bIsVisible = bIsLayerVisible;

    return std::make_pair(layerName, LayerData);
}
