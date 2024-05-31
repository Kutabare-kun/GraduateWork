#pragma once
#include "../Core/Allocator/ResourceAllocator.h"
#include "../Core/Resource/Font/FontResource.h"
#include "../Core/Resource/Texture/TextureResource.h"

class Game
{
public:
    Game();

    void CaptureInput();
    void Update();
    void LateUpdate();
    void UpdateDeltaTime(float NewDeltaTime) { DeltaTime = NewDeltaTime; }
    void Draw();

    static bool bIsExitGame;

private:
    ResourceAllocator<TextureResource> TextureAllocator;
    ResourceAllocator<FontResource> FontAllocator;

    float DeltaTime;
};
