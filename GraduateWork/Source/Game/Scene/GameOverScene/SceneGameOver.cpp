#include "SceneGameOver.h"

SceneGameOver::SceneGameOver(ResourceAllocator<TextureResource>& TextureAllocator,
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
    GameOver = std::make_unique<GameOverWidget>(MainObject.get(), Slot{
                                                          Padding{0.0f},
                                                          Crop{0.0f},
                                                          Rectangle{
                                                              0.0f, 0.0f,
                                                              WindowX, WindowY
                                                          }
                                                      }, nullptr);
}

void SceneGameOver::OnCreate()
{
    GameOver->Awake();
}

void SceneGameOver::Update(float DeltaTime)
{
    GameOver->Update(DeltaTime);
}

void SceneGameOver::Draw()
{
    GameOver->Draw();
}
