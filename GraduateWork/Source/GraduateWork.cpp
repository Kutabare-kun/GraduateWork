#include "Core/Window/Window.h"
#include "Game/Game.h"

int main(int Argc, char* Argv[])
{
    Window::GetInstance().Init(
        {1200.0f, 720.0f},//{static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())},
        "Graduate Work"
    );

    SetTargetFPS(3000);

    Game MyGame;

    while (!WindowShouldClose())
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
