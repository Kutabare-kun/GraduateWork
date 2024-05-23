#pragma once
#include "../../../Core/Allocator/ResourceAllocator.h"
#include "../../../Core/Resource/Texture/TextureResource.h"
#include "../../../Core/SceneManager/Scene/Scene.h"
#include "../../UI/Widgets/WidgetSplashScreen.h"

class SceneSplashScreen
    : public Scene
{
public:
    SceneSplashScreen(ResourceAllocator<TextureResource>& TextureAllocator,
                      ResourceAllocator<FontResource>& FontAllocator);

    void OnActivate() override;

    void SetSwitchToScene(unsigned Id);

    void Update(float DeltaTime) override;
    void Draw() override;

private:
    float Timer;
    float TimerLimit;
    unsigned SwitchToScene;

    ResourceAllocator<TextureResource>& TextureAllocator;
    ResourceAllocator<FontResource>& FontAllocator;

    std::unique_ptr<WidgetSplashScreen> SplashScreenWidget;
    std::unique_ptr<Object> SplashScreenObject;

    SharedContext Context;
};
