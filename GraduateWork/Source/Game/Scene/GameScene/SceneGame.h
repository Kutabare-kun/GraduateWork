#pragma once
#include "../../../Core/Allocator/ResourceAllocator.h"
#include "../../../Core/SceneManager/Scene/Scene.h"
#include "../../../Core/Collection/ObjectCollection.h"

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
    std::unique_ptr<ObjectCollection> Objects;
};
