#include "SceneGame.h"

SceneGame::SceneGame(Directory& NewDirectory, ResourceAllocator<TextureResource>& NewTextureAllocator)
    : WorkingDirectory(NewDirectory), TextureAllocator(NewTextureAllocator)
{
    Objects = std::make_unique<ObjectCollection>();
}

void SceneGame::OnCreate()
{
}

void SceneGame::OnDestroy()
{
}

void SceneGame::ProcessInput()
{
}

void SceneGame::Update(float DeltaTime)
{
    Objects->ProcessRemovals();
    Objects->ProcessNewObjects();
    
    Objects->Update(DeltaTime);
}

void SceneGame::LateUpdate(float DeltaTime)
{
    Objects->LateUpdate(DeltaTime);
}

void SceneGame::Draw()
{
    Objects->Draw();
}
