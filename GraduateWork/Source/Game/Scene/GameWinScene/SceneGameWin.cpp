#include "SceneGameWin.h"

SceneGameWin::SceneGameWin(ResourceAllocator<TextureResource>& TextureAllocator,
                           ResourceAllocator<FontResource>& FontAllocator)
    : TextureAllocator(TextureAllocator), FontAllocator(FontAllocator)
{
    Context.Objects = nullptr;
    Context.TextureAllocator = &TextureAllocator;
    Context.FontAllocator = &FontAllocator;
    Context.RaycastSys = nullptr;
    Context.TimerManagerSys = nullptr;

    const auto [WindowX, WindowY] = Window::GetInstance().GetScreenSize();

    MainObject = std::make_unique<Object>(&Context);
    GameWin = std::make_unique<GameWinWidget>(MainObject.get(), Slot{
                                                          Padding{0.0f},
                                                          Crop{0.0f},
                                                          Rectangle{
                                                              0.0f, 0.0f,
                                                              WindowX, WindowY
                                                          }
                                                      }, nullptr);
}

void SceneGameWin::OnCreate()
{
    GameWin->Awake();
}

void SceneGameWin::Update(float DeltaTime)
{
    GameWin->Update(DeltaTime);
}

void SceneGameWin::Draw()
{
    GameWin->Draw();
}
