#pragma once
#include "../../../Core/Algorithm/Raycast/Raycast.h"
#include "../../../Core/Allocator/ResourceAllocator.h"
#include "../../../Core/SceneManager/Scene/Scene.h"
#include "../../../Core/Collection/ObjectCollection.h"
#include "../../../Core/Component/Camera/CameraComponent.h"
#include "../../../Core/Parser/TileMapParser/TileMapParser.h"
#include "../../../Core/Timer/Manager/TimerManager.h"

class PlayerHUD;
class MovementComponent;
class TextureResource;
class Directory;

class SceneGame
    : public Scene
{
public:
    SceneGame(Directory& NewDirectory, ResourceAllocator<TextureResource>& NewTextureAllocator, ResourceAllocator<FontResource>& NewFontAllocator);
    
    void OnCreate() override;
    void OnDestroy() override;
    
    void ProcessInput() override;
    void Update(float DeltaTime) override;
    void LateUpdate(float DeltaTime) override;
    void Draw() override;

private:
    Directory& WorkingDirectory;
    ResourceAllocator<TextureResource>& TextureAllocator;
    ResourceAllocator<FontResource>& FontAllocator;

    std::unique_ptr<TileMapParser> MapParser;
    
    std::unique_ptr<ObjectCollection> Objects;
    std::shared_ptr<MovementComponent> PlayerMovement;
    std::shared_ptr<CameraComponent> Camera;

    SharedContext Context;
    std::unique_ptr<DrawableSystem> DrawableSys;
    std::unique_ptr<ColliderSystem> ColliderSys;
    std::unique_ptr<Quadtree> CollisionTree;
    std::unique_ptr<Raycast> RaycastSys;
    std::unique_ptr<TimerManager> TimerManagerSys;

    std::shared_ptr<PlayerHUD> HUD;
};
