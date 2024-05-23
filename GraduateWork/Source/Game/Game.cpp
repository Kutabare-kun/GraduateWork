#include "Game.h"

#include <raylib.h>

#include "Scene/GameScene/SceneGame.h"
#include "Scene/MainScene/MainScene.h"
#include "Scene/SceneSplashScreen/SceneSplashScreen.h"

bool Game::bIsExitGame = false;

Game::Game()
{
    std::shared_ptr<SceneSplashScreen> SplashScreen = std::make_shared<SceneSplashScreen>(
        TextureAllocator, FontAllocator);
    std::shared_ptr<SceneGame> GameScene = std::make_shared<SceneGame>(TextureAllocator, FontAllocator);
    std::shared_ptr<MainScene> SceneMain = std::make_shared<MainScene>(TextureAllocator, FontAllocator);

    unsigned SplashScreenID = SceneStateMachine::GetInstance().Add(SplashScreen);
    unsigned GameSceneID = SceneStateMachine::GetInstance().Add(GameScene);
    unsigned MainSceneID = SceneStateMachine::GetInstance().Add(SceneMain);

    SplashScreen->SetSwitchToScene(GameSceneID);
    SceneStateMachine::GetInstance().SwitchTo(MainSceneID);

    UpdateDeltaTime(GetFrameTime());
}

void Game::CaptureInput()
{
    SceneStateMachine::GetInstance().ProcessInput();

    // DEBUG INPUT
    if (IsKeyPressed(KEY_F1))
    {
        SceneStateMachine::GetInstance().SwitchTo(0);
        SceneStateMachine::GetInstance().Remove(1);

        std::shared_ptr<SceneGame> GameScene = std::make_shared<SceneGame>(TextureAllocator, FontAllocator);
        unsigned GameSceneID = SceneStateMachine::GetInstance().Add(GameScene);

        std::shared_ptr<Scene> Splash = SceneStateMachine::GetInstance().GetScene(0);
        std::dynamic_pointer_cast<SceneSplashScreen>(Splash)->SetSwitchToScene(GameSceneID);
    }
    // ~DEBUG INPUT
}

void Game::Update()
{
    SceneStateMachine::GetInstance().Update(GetFrameTime());
}

void Game::LateUpdate()
{
    SceneStateMachine::GetInstance().LateUpdate(GetFrameTime());
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(DARKGRAY);

    SceneStateMachine::GetInstance().Draw();

    DrawFPS(10, 10);

    EndDrawing();
}
