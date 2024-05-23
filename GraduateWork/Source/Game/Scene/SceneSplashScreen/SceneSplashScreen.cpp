#include "SceneSplashScreen.h"

#include "../../../Core/Allocator/ResourceAllocator.h"
#include "../../../Core/Directory/Directory.h"
#include "../../../Core/SceneManager/SceneStateMachine.h"
#include "../../../Core/Window/Window.h"

SceneSplashScreen::SceneSplashScreen(ResourceAllocator<TextureResource>& TextureAllocator,
                                     ResourceAllocator<FontResource>& FontAllocator)
    : TextureAllocator(TextureAllocator),
      FontAllocator(FontAllocator)
{
    Timer = 0.0f;
    TimerLimit = 3.0f;

    Context.Objects = nullptr;
    Context.TextureAllocator = &TextureAllocator;
    Context.FontAllocator = &FontAllocator;
    Context.RaycastSys = nullptr;
    Context.TimerManagerSys = nullptr;

    const auto& [ScreenX, ScreenY] = Window::GetInstance().GetScreenSize();

    SplashScreenObject = std::make_unique<Object>(&Context);
    SplashScreenWidget = std::make_unique<WidgetSplashScreen>(SplashScreenObject.get(), Slot{
                                                                  Padding{0.0f},
                                                                  Crop{0.0f},
                                                                  Rectangle{
                                                                      0.0f, 0.0f,
                                                                      ScreenX, ScreenY
                                                                  }
                                                              }, nullptr);
}

void SceneSplashScreen::OnActivate()
{
    Timer = 0.0f;

    SplashScreenWidget->Awake();
}

void SceneSplashScreen::SetSwitchToScene(unsigned Id)
{
    SwitchToScene = Id;
}

void SceneSplashScreen::Update(float DeltaTime)
{
    SplashScreenWidget->Update(DeltaTime);

    Timer += DeltaTime;

    if (Timer >= TimerLimit)
    {
        SceneStateMachine::GetInstance().SwitchTo(SwitchToScene);
    }
}

void SceneSplashScreen::Draw()
{
    // Draw splash screen
    SplashScreenWidget->Draw();

    Vector2 ScreenSize = Window::GetInstance().GetScreenSize();

    DrawText(TextFormat("%f", TimerLimit - Timer), static_cast<int>(ScreenSize.x - 200.0f),
             static_cast<int>(ScreenSize.y - 20.0f), 20, RED);
}
