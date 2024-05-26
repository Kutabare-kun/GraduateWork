#include "Game.h"

#include <raylib.h>

#include "Scene/GameOverScene/SceneGameOver.h"
#include "Scene/GameScene/SceneGame.h"
#include "Scene/GameWinScene/SceneGameWin.h"
#include "Scene/MainScene/MainScene.h"
#include "Scene/SceneSplashScreen/SceneSplashScreen.h"

bool Game::bIsExitGame = false;

Game::Game()
{
    std::shared_ptr<SceneSplashScreen> SplashScreen = std::make_shared<SceneSplashScreen>(
        TextureAllocator, FontAllocator);
    std::shared_ptr<SceneGame> GameScene = std::make_shared<SceneGame>(TextureAllocator, FontAllocator);
    std::shared_ptr<MainScene> SceneMain = std::make_shared<MainScene>(TextureAllocator, FontAllocator);
    std::shared_ptr<SceneGameOver> GameOverScene = std::make_shared<SceneGameOver>(TextureAllocator, FontAllocator);
    std::shared_ptr<SceneGameWin> GameWinScene = std::make_shared<SceneGameWin>(TextureAllocator, FontAllocator);

    SceneStateMachine::GetInstance().Add(SplashScreen);
    SceneStateMachine::GetInstance().Add(GameOverScene);
    SceneStateMachine::GetInstance().Add(GameWinScene);

    unsigned GameSceneID = SceneStateMachine::GetInstance().Add(GameScene);
    unsigned MainSceneID = SceneStateMachine::GetInstance().Add(SceneMain);

    SplashScreen->SetSwitchToScene(GameSceneID);
    SceneStateMachine::GetInstance().SwitchTo(MainSceneID);

    UpdateDeltaTime(GetFrameTime());
}

void Game::CaptureInput()
{
    SceneStateMachine::GetInstance().ProcessInput();
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
