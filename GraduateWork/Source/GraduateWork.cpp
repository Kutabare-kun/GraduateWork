#include <filesystem>

#include "Actors/Enemy/Enemy.h"
#include "World/World.h"
#include "Actors/Player/Player.h"
#include "GameRule/GameMode/Gamemode.h"
#include "GameRule/GameState/Gamestate.h"


// Main Path
const std::string CurrentPath = std::filesystem::current_path().string().erase(std::filesystem::current_path().string().find_last_of('\\'));

const int ScreenWidth = 1600;
const int ScreenHeight = 800;

int main(int Argc, char* Argv[])
{
    InitWindow(ScreenWidth, ScreenHeight, "Graduate Work");

    SetTargetFPS(3000);

    World::GetInstance().InitWorld();
    World::GetInstance().CreateActor<Enemy>(CurrentPath + R"(\Resource\Texture\Enemy.png)", Vector2{500.0f, 500.0f});
    
    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        World::GetInstance().EventTick(GetFrameTime());
        // ~Update

        Camera2D Camera = Gamestate::GetInstance().GetPlayer<Player>()->GetCamera();

        // Draw
        BeginDrawing();
            BeginMode2D(Camera);
            ClearBackground(DARKBLUE);

            World::GetInstance().Draw();

            EndMode2D();
            DrawCircle(35, 60, 36, DARKGRAY);
            DrawText("W", 30, 30, 20, IsKeyDown(KEY_W) ? GREEN : RED);
            DrawText("A", 10, 50, 20, IsKeyDown(KEY_A) ? GREEN : RED);
            DrawText("S", 30, 70, 20, IsKeyDown(KEY_S) ? GREEN : RED);
            DrawText("D", 50, 50, 20, IsKeyDown(KEY_D) ? GREEN : RED);

            const int FPS = GetFPS();
            DrawText(TextFormat("FPS: %i", FPS), 10, 10, 20, FPS >= 60 ? GREEN : FPS >= 30 ? YELLOW : RED);
        EndDrawing();
        // ~Draw
    }

    World::GetInstance().EventEnd();

    // De-Initialization
    CloseWindow();
    
    return 0;
}
