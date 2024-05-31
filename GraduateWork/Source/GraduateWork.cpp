#include "Core/Window/Window.h"
#include "Game/Game.h"

int main(int Argc, char* Argv[])
{
    Window::GetInstance().Init(
        {1200.0f, 720.0f},
        "Graduate Work"
    );

    SetTargetFPS(3000);
    SetExitKey(KEY_NULL);

    Game MyGame;

    while (!WindowShouldClose() && !Game::bIsExitGame)
    {
        MyGame.CaptureInput();
        MyGame.Update();
        MyGame.LateUpdate();
        MyGame.Draw();

        MyGame.UpdateDeltaTime(GetFrameTime());
    }

    Window::GetInstance().Close();

    return 0;
}
