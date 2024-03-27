#include "SceneSplashScreen.h"

#include "../../../Core/Allocator/ResourceAllocator.h"
#include "../../../Core/Directory/Directory.h"
#include "../../../Core/SceneManager/SceneStateMachine.h"
#include "../../../Core/Window/Window.h"

SceneSplashScreen::SceneSplashScreen(Directory& WorkingDir, SceneStateMachine& StateMachine,
                                     ResourceAllocator<TextureResource>& TextureAllocator)
    : WorkingDir(WorkingDir),
      StateMachine(StateMachine),
      TextureAllocator(TextureAllocator)

{
    Timer = 0.0f;
    TimerLimit = 3.0f;
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
}

void SceneSplashScreen::SetSwitchToScene(unsigned Id)
{
    SwitchToScene = Id;
}

void SceneSplashScreen::Update(float DeltaTime)
{
    Timer += DeltaTime;

    if (Timer >= TimerLimit)
    {
        StateMachine.SwitchTo(SwitchToScene);
    }
}

void SceneSplashScreen::Draw()
{
    // Draw splash screen at the top left corner
    DrawTextureEx(SplashTexture, {0, 0}, 0.0f, 10.0f, WHITE);

    Vector2 ScreenSize = Window::GetInstance().GetScreenSize();

    DrawText(TextFormat("%f", TimerLimit - Timer), static_cast<int>(ScreenSize.x - 200.0f), static_cast<int>(ScreenSize.y - 20.0f), 20, RED);
}
