#pragma once
#include "../../../Core/Allocator/ResourceAllocator.h"
#include "../../../Core/Resource/Texture/TextureResource.h"
#include "../../../Core/SceneManager/Scene/Scene.h"

class SceneStateMachine;
class Directory;

class SceneSplashScreen
    : public Scene
{
public:
    SceneSplashScreen(Directory& WorkingDir, SceneStateMachine& StateMachine, ResourceAllocator<TextureResource>& TextureAllocator);

    void OnCreate() override;
    void OnDestroy() override;

    void OnActivate() override;

    void SetSwitchToScene(unsigned Id);

    void Update(float DeltaTime) override;
    void Draw() override;

private:
    Texture2D SplashTexture;
    float Timer;
    float TimerLimit;
    unsigned SwitchToScene;
    
    Directory& WorkingDir;
    SceneStateMachine& StateMachine;

    ResourceAllocator<TextureResource>& TextureAllocator;
};
