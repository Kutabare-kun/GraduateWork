#pragma once
#include "../../../Core/SceneManager/Scene/Scene.h"
#include "../../../Core/Allocator/ResourceAllocator.h"
#include "../../../Core/Object/Object.h"
#include "../../../Core/Resource/Font/FontResource.h"
#include "../../../Core/Resource/Texture/TextureResource.h"
#include "../../UI/Widgets/GameOverWidget/GameOverWidget.h"

class SceneGameOver
    : public Scene
{
public:
    SceneGameOver(ResourceAllocator<TextureResource>& TextureAllocator,
                  ResourceAllocator<FontResource>& FontAllocator);

    void OnCreate() override;

    void Update(float DeltaTime) override;
    void Draw() override;

private:
    ResourceAllocator<TextureResource>& TextureAllocator;
    ResourceAllocator<FontResource>& FontAllocator;

    std::unique_ptr<Object> MainObject;
    std::unique_ptr<GameOverWidget> GameOver;

    SharedContext Context;
};
