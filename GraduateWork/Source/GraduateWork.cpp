#include "SmartPtr/SmartTexture.h"

int main(int argc, char* argv[])
{
    constexpr int ScreenWidth = 800;
    constexpr int ScreenHeight = 450;
    
    InitWindow(ScreenWidth, ScreenHeight, "Graduate Work");

    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose())
    {
        // Update

        // ~Update

        // Draw
        BeginDrawing();

        

        EndDrawing();
        // ~Draw
    }

    // De-Initialization
    CloseWindow();
    
    return 0;
}
