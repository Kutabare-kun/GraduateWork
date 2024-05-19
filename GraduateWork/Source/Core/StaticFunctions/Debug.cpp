#include "Debug.h"

#include <iostream>
#include <format>

void Debug::Draw(const Camera2D& OwnerCamera)
{
    constexpr float LineThickness = 5.0f;

    BeginMode2D(OwnerCamera);

    for (auto& [Rect, Color] : Rectangles)
    {
        DrawRectangleLinesEx(Rect, LineThickness, Color);
    }

    for (auto& [Line, Color] : Lines)
    {
        DrawLineEx(Line[0], Line[1], LineThickness, Color);
    }

    for (auto& [Pixel, Color] : Pixels)
    {
        DrawPixelV(Pixel, Color);
    }

    EndMode2D();

    Rectangles.clear();
    Lines.clear();
    Pixels.clear();
}

void Debug::DrawRectangle(const Rectangle& Rect, const Color& Color)
{
    Rectangles.emplace_back(Rect, Color);
}

void Debug::DrawLine(const Vector2& Start, const Vector2& End, const Color& Color)
{
    Lines.emplace_back(std::array<Vector2, 2>{Start, End}, Color);
}

void Debug::DrawPixel(const Vector2& Position, const Color& Color)
{
    Pixels.emplace_back(Position, Color);
}

void Debug::Log(const std::string& Message)
{
    std::cout << std::format("[LOG] {}", Message) << std::endl;
}

void Debug::LogWarning(const std::string& Message)
{
    std::cout << std::format("[WARNING] {}", Message) << std::endl;
}

void Debug::LogError(const std::string& Message)
{
    std::cout << std::format("[ERROR] {}", Message) << std::endl;
}
