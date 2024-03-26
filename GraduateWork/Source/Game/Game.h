#pragma once
#include "../Core/Allocator/ResourceAllocator.h"
#include "../Core/Directory/Directory.h"
#include "../Core/Resource/Texture/TextureResource.h"
#include "../Core/SceneManager/SceneStateMachine.h"

class Game
{
public:
    Game();

    void CaptureInput();
    void Update();
    void LateUpdate();
    void UpdateDeltaTime(float NewDeltaTime) { DeltaTime = NewDeltaTime; }
    void Draw();

private:
    ResourceAllocator<TextureResource> TextureAllocator;
    SceneStateMachine& StateMachine;
    Directory& WorkingDir;

    float DeltaTime;
};
