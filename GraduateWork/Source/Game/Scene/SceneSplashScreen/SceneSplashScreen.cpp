#include "SceneSplashScreen.h"

#include "../../../Core/Allocator/ResourceAllocator.h"
#include "../../../Core/Directory/Directory.h"
#include "../../../Core/SceneManager/SceneStateMachine.h"
#include "../../../Core/Window/Window.h"

SceneSplashScreen::SceneSplashScreen(Directory& WorkingDir, SceneStateMachine& StateMachine,
                                     ResourceAllocator<TextureResource>& TextureAllocator,
                                     ResourceAllocator<FontResource>& FontAllocator)
    : WorkingDir(WorkingDir),
      StateMachine(StateMachine),
      TextureAllocator(TextureAllocator),
      FontAllocator(FontAllocator)
{
    Timer = 0.0f;
    TimerLimit = 3.0f;

    Context.Objects = nullptr;
    Context.TextureAllocator = &TextureAllocator;
    Context.FontAllocator = &FontAllocator;
    Context.RaycastSys = nullptr;
    Context.TimerManagerSys = nullptr;

    SplashScreenObject = std::make_unique<Object>(&Context, nullptr);
    SplashScreenWidget = std::make_unique<WidgetSplashScreen>(SplashScreenObject.get(), Slot{
                                                                  Padding{0.0f},
                                                                  Crop{0.0f},
                                                                  Rectangle{
                                                                      0.0f, 0.0f, static_cast<float>(GetScreenWidth()),
                                                                      static_cast<float>(GetScreenHeight())
                                                                  }
                                                              }, nullptr);
}

void SceneSplashScreen::OnCreate()
{
    int Id = TextureAllocator.Add(WorkingDir.GetTexture("MetalPlate.png"));
    if (Id >= 0) SplashTexture = TextureAllocator.Get(Id)->Get();
}

void SceneSplashScreen::OnDestroy()
{
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
        StateMachine.SwitchTo(SwitchToScene);
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
