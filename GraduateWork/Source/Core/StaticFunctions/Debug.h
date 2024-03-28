#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include <array>

#include "../Pattern/Singleton.h"

class Debug
    : public Singleton<Debug>
{
public:
    void Draw();
    void DrawRectangle(const Rectangle& Rect, const Color& Color = { 255, 0, 0, 255 });
    void DrawLine(const Vector2& Start, const Vector2& End, const Color& Color = { 255, 0, 0, 255 });
    
    void Log(const std::string& Message);
    void LogWarning(const std::string& Message);
    void LogError(const std::string& Message);

private:
    std::vector<std::pair<std::array<Vector2, 2>, Color>> Lines;
    std::vector<std::pair<Rectangle, Color>> Rectangles;
};