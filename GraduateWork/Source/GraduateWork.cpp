#include <filesystem>

#include "Actors/Enemy/Enemy.h"
#include "Actors/Obstacle/Obstacle.h"
#include "World/World.h"
#include "Actors/Player/Player.h"
#include "GameRule/GameMode/Gamemode.h"
#include "GameRule/GameState/Gamestate.h"


// Main Path
const std::string CurrentPath = std::filesystem::current_path().string().erase(std::filesystem::current_path().string().find_last_of('\\'));

const int ScreenWidth = 800;
const int ScreenHeight = 400;

int main(int Argc, char* Argv[])
{
    InitWindow(ScreenWidth, ScreenHeight, "Graduate Work");

    SetTargetFPS(60);

    World::GetInstance().InitWorld();
    World::GetInstance().CreateActor<Enemy>(CurrentPath + R"(\Resource\Texture\Enemy.png)", Vector2{400.0f, 400.0f});
    
    for (int i = 0; i < 3; ++i)
    {
        World::GetInstance().CreateObstacle<Obstacle>(CurrentPath + R"(\Resource\Texture\Obstacle.png)", Vector2{200.0f + i * 64, 200.0f});
    }

    for (int i = 1; i < 3; ++i)
    {
        World::GetInstance().CreateObstacle<Obstacle>(CurrentPath + R"(\Resource\Texture\Obstacle.png)", Vector2{200.0f, 200.0f + i * 64});
    }

    World::GetInstance().CreateObstacle<Obstacle>(CurrentPath + R"(\Resource\Texture\Obstacle.png)", Vector2{500.0f, 200.0f});
    
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
        
        {   // DELETE THIS
            int CellSize = 25;
            int Multiplier = 2;
            for (int i = 0; i < ScreenWidth * Multiplier; i += CellSize)
            {
                for (int j = 0; j < ScreenHeight * Multiplier; j += CellSize)
                {
                    DrawRectangleLines(i, j, CellSize, CellSize, WHITE);
                }
            }
        }   // ~DELETE THIS

            World::GetInstance().Draw();

            EndMode2D();
            int FPS = GetFPS();
            DrawText(TextFormat("FPS: %i", FPS), 10, 10, 20, FPS >= 60 ? GREEN : FPS >= 30 ? YELLOW : RED);

            DrawText("W", 30, 30, 20, IsKeyDown(KEY_W) ? GREEN : RED);
            DrawText("A", 10, 50, 20, IsKeyDown(KEY_A) ? GREEN : RED);
            DrawText("S", 30, 70, 20, IsKeyDown(KEY_S) ? GREEN : RED);
            DrawText("D", 50, 50, 20, IsKeyDown(KEY_D) ? GREEN : RED);
        EndDrawing();
        // ~Draw
    }

    World::GetInstance().EventEnd();

    // De-Initialization
    CloseWindow();
    
    return 0;
}
