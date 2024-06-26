#include "Window.h"

void Window::Init(const Vector2& ScreenSize, const std::string& Title)
{
    this->Title = Title;

    InitWindow(static_cast<int>(ScreenSize.x), static_cast<int>(ScreenSize.y), Title.c_str());
    SetWindowState(FLAG_WINDOW_RESIZABLE);
}

void Window::Close()
{
    CloseWindow();
}

const Vector2& Window::GetScreenSize() const
{
    return {static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())};
}

const std::string& Window::GetTitle() const
{
    return Title;
}

void Window::FlipFullscreen()
{
    if (!IsWindowFullscreen())
        ToggleFullscreen();
}
