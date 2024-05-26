#include "Core/Window/Window.h"
#include "Game/Game.h"

int main(int Argc, char* Argv[])
{
    Window::GetInstance().Init(
        {1200.0f, 720.0f},
        "Graduate Work"
    );

    SetTargetFPS(3000);

    Game MyGame;

    SetExitKey(KEY_NULL);

    while (!WindowShouldClose() && !Game::bIsExitGame)
    {
        MyGame.CaptureInput();
        MyGame.Update();
        MyGame.LateUpdate();
        MyGame.Draw();

        MyGame.UpdateDeltaTime(GetFrameTime());
    }

    CloseWindow();

    return 0;
}
