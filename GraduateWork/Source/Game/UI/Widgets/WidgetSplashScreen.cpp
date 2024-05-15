#include "WidgetSplashScreen.h"

#include "../../../Core/UI/Image/UIImage.h"

WidgetSplashScreen::WidgetSplashScreen(Object* Owner, const Slot& LayoutSlot, UIBase* Parent)
    : UIPanel(Owner, LayoutSlot, Parent)
{
}

void WidgetSplashScreen::Awake()
{
    std::shared_ptr<UIImage> SplashScreenImage = std::make_shared<UIImage>(
        GetOwner(), Slot{
            Padding{0.0f},
            Rectangle{0.0f, 0.0f, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())}
        }, this, "MetalPlate.png");
    AddChild(SplashScreenImage);

    UIPanel::Awake();
}

void WidgetSplashScreen::Update(float DeltaTime)
{
    UIPanel::Update(DeltaTime);
}

void WidgetSplashScreen::Draw()
{
    UIPanel::Draw();
}