#include "Game.h"

#include <raylib.h>

#include "Scene/GameScene/SceneGame.h"
#include "Scene/SceneSplashScreen/SceneSplashScreen.h"

Game::Game()
    : StateMachine(SceneStateMachine::GetInstance()),
      WorkingDir(Directory::GetInstance())
{
    std::shared_ptr<SceneSplashScreen> SplashScreen = std::make_shared<SceneSplashScreen>(WorkingDir, StateMachine, TextureAllocator);
    std::shared_ptr<SceneGame> GameScene = std::make_shared<SceneGame>(WorkingDir, TextureAllocator);

    unsigned SplashScreenID = StateMachine.Add(SplashScreen);
    unsigned GameSceneID = StateMachine.Add(GameScene);

    SplashScreen->SetSwitchToScene(GameSceneID);
    StateMachine.SwitchTo(SplashScreenID);

    UpdateDeltaTime(GetFrameTime());
}

void Game::CaptureInput()
{
    StateMachine.ProcessInput();
}

void Game::Update()
{
    StateMachine.Update(GetFrameTime());
}

void Game::LateUpdate()
{
    StateMachine.LateUpdate(GetFrameTime());
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    StateMachine.Draw();

    DrawFPS(10, 10);
    
    EndDrawing();
}
