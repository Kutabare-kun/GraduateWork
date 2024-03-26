#pragma once
#include "../../../Core/Allocator/ResourceAllocator.h"
#include "../../../Core/SceneManager/Scene/Scene.h"
#include "../../../Core/Collection/ObjectCollection.h"
#include "../../../Core/Parser/TileMapParser/TileMapParser.h"

class MovementComponent;
class TextureResource;
class Directory;

class SceneGame
    : public Scene
{
public:
    SceneGame(Directory& NewDirectory, ResourceAllocator<TextureResource>& NewTextureAllocator);
    
    void OnCreate() override;
    void OnDestroy() override;
    
    void ProcessInput() override;
    void Update(float DeltaTime) override;
    void LateUpdate(float DeltaTime) override;
    void Draw() override;

private:
    Directory& WorkingDirectory;
    ResourceAllocator<TextureResource>& TextureAllocator;

    std::unique_ptr<TileMapParser> MapParser;
    
    std::unique_ptr<ObjectCollection> Objects;
    std::shared_ptr<MovementComponent> PlayerMovement;
};
