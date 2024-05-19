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
    void Draw(const Camera2D& OwnerCamera);
    void DrawRectangle(const Rectangle& Rect, const Color& Color = {255, 0, 0, 255});
    void DrawLine(const Vector2& Start, const Vector2& End, const Color& Color = {255, 0, 0, 255});
    void DrawPixel(const Vector2& Position, const Color& Color = {255, 0, 0, 255});
    void DrawText(const std::string& Text, const Vector2& Position, int FontSize = 24,
                  const Color& Color = {255, 0, 0, 255});

    void Log(const std::string& Message);
    void LogWarning(const std::string& Message);
    void LogError(const std::string& Message);

private:
    void Clear();

    std::vector<std::pair<std::array<Vector2, 2>, Color>> Lines;
    std::vector<std::pair<Vector2, Color>> Pixels;
    std::vector<std::pair<Rectangle, Color>> Rectangles;
    std::vector<std::tuple<std::string, Vector2, int, Color>> Texts;
};
