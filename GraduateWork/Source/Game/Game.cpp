#include "Game.h"

#include <raylib.h>

#include "Scene/GameScene/SceneGame.h"
#include "Scene/SceneSplashScreen/SceneSplashScreen.h"

Game::Game()
    : StateMachine(SceneStateMachine::GetInstance()),
      WorkingDir(Directory::GetInstance())
{
    std::shared_ptr<SceneSplashScreen> SplashScreen = std::make_shared<SceneSplashScreen>(
        WorkingDir, StateMachine, TextureAllocator, FontAllocator);
    std::shared_ptr<SceneGame> GameScene = std::make_shared<SceneGame>(WorkingDir, TextureAllocator, FontAllocator);

    unsigned SplashScreenID = StateMachine.Add(SplashScreen);
    unsigned GameSceneID = StateMachine.Add(GameScene);

    SplashScreen->SetSwitchToScene(GameSceneID);
    StateMachine.SwitchTo(SplashScreenID);

    UpdateDeltaTime(GetFrameTime());
}

void Game::CaptureInput()
{
    StateMachine.ProcessInput();

    // DEBUG INPUT
    if (IsKeyPressed(KEY_F1))
    {
        StateMachine.SwitchTo(0);
        StateMachine.Remove(1);

        std::shared_ptr<SceneGame> GameScene = std::make_shared<SceneGame>(WorkingDir, TextureAllocator, FontAllocator);
        unsigned GameSceneID = StateMachine.Add(GameScene);

        std::shared_ptr<Scene> Splash = StateMachine.GetScene(0);
        std::dynamic_pointer_cast<SceneSplashScreen>(Splash)->SetSwitchToScene(GameSceneID);
    }
    // ~DEBUG INPUT
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
    ClearBackground(DARKGRAY);

    StateMachine.Draw();

    DrawFPS(10, 10);

    EndDrawing();
}
