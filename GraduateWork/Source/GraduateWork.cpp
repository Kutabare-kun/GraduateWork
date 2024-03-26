#include "Core/Window/Window.h"
#include "Game/Game.h"

int main(int Argc, char* Argv[])
{
    Window::GetInstance().Init({1600, 800}, "Graduate Work");

    SetTargetFPS(3000);

    Game MyGame;

    while (!WindowShouldClose())
    {
        MyGame.Update();
        MyGame.LateUpdate();
        MyGame.Draw();
        
        MyGame.UpdateDeltaTime(GetFrameTime());
    }

    CloseWindow();
    
    return 0;
}
