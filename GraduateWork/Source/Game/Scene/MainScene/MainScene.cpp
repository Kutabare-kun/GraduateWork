#include "MainScene.h"

MainScene::MainScene(ResourceAllocator<TextureResource>& TextureAllocator,
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
    MainWidget = std::make_unique<MainWidgetScreen>(MainObject.get(), Slot{
        Padding{0.0f},
        Crop{0.0f},
        Rectangle{
            0.0f, 0.0f,
            WindowX, WindowY
        }
    }, nullptr);
}

void MainScene::OnCreate()
{
    MainWidget->Awake();
}

void MainScene::Update(float DeltaTime)
{
    MainWidget->Update(DeltaTime);
}

void MainScene::Draw()
{
    MainWidget->Draw();
}
