#include "Debug.h"

#include <iostream>
#include <format>

void Debug::Draw()
{
    constexpr float LineThickness = 5.0f;
    
    for (auto& [Rect, Color] : Rectangles)
    {
        DrawRectangleLinesEx(Rect, LineThickness, Color);
    }

    for (auto& [Line, Color] : Lines)
    {
        DrawLineEx(Line[0], Line[1], LineThickness, Color);
    }

    Rectangles.clear();
    Lines.clear();
}

void Debug::DrawRectangle(const Rectangle& Rect, const Color& Color)
{
    Rectangles.emplace_back(Rect, Color);
}

void Debug::DrawLine(const Vector2& Start, const Vector2& End, const Color& Color)
{
    Lines.emplace_back(std::array<Vector2, 2>{Start, End}, Color);
}

void Debug::Log(const std::string& Message)
{
    std::cout << std::format("[LOG] {}\n", Message);
}

void Debug::LogWarning(const std::string& Message)
{
    std::cout << std::format("[WARNING] {}\n", Message);
}

void Debug::LogError(const std::string& Message)
{
    std::cout << std::format("[ERROR] {}\n", Message);
}
