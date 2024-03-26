#pragma once
#include <string>
#include <raylib.h>

#include "../Pattern/Singleton.h"

class Window
    : public Singleton<Window>
{
public:
    void Init(const Vector2& ScreenSize, const std::string& Title);
    void Close();

    const Vector2& GetScreenSize() const;
    const std::string& GetTitle() const;
    
private:
    Vector2 ScreenSize;
    std::string Title;
};
