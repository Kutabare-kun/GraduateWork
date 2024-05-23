#pragma once
#include "../../../Core/SceneManager/Scene/Scene.h"
#include "../../../Core/Allocator/ResourceAllocator.h"
#include "../../../Core/Object/Object.h"
#include "../../../Core/Resource/Font/FontResource.h"
#include "../../../Core/Resource/Texture/TextureResource.h"
#include "../../UI/Widgets/GameWinWidget/GameWinWidget.h"

class SceneGameWin
    : public Scene
{
public:
    SceneGameWin(ResourceAllocator<TextureResource>& TextureAllocator,
                 ResourceAllocator<FontResource>& FontAllocator);

    void OnCreate() override;

    void Update(float DeltaTime) override;
    void Draw() override;

private:
    ResourceAllocator<TextureResource>& TextureAllocator;
    ResourceAllocator<FontResource>& FontAllocator;

    std::unique_ptr<Object> MainObject;
    std::unique_ptr<GameWinWidget> GameWin;

    SharedContext Context;
};
