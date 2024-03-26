#include "Window.h"

void Window::Init(const Vector2& ScreenSize, const std::string& Title)
{
    this->ScreenSize = ScreenSize;
    this->Title = Title;

    InitWindow(ScreenSize.x, ScreenSize.y, Title.c_str());
}

void Window::Close()
{
    CloseWindow();
}

const Vector2& Window::GetScreenSize() const
{
    return ScreenSize;
}

const std::string& Window::GetTitle() const
{
    return Title;
}
