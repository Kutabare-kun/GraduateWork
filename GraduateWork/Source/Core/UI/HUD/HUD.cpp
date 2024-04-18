#include "HUD.h"

HUD::HUD(Object* Owner)
    : Owner(Owner)
{
}

void HUD::Awake()
{
    for (auto& Element : Widgets)
    {
        Element->Awake();
    }
}

void HUD::Draw()
{
    for (const auto& Widget : ShowWidgets)
    {
        Widget->Draw();
    }
}

void HUD::Update(float DeltaTime)
{
    for (auto& Element : ShowWidgets)
    {
        Element->Update(DeltaTime);
    }
}

std::shared_ptr<UIObject> HUD::GetWidget(UIObject* Widget)
{
    for (const auto& ExistingWidget : Widgets)
    {
        if (ExistingWidget.get() == Widget)
        {
            return ExistingWidget;
        }
    }

    return nullptr;
}

bool HUD::RemoveWidget(std::shared_ptr<UIObject> Widget)
{
    const auto FoundWidget = std::find(Widgets.cbegin(), Widgets.cend(), Widget);
    const auto FoundShowWidget = std::find(ShowWidgets.cbegin(), ShowWidgets.cend(), Widget);

    bool bRemoved = false;
    
    if (FoundWidget != Widgets.cend())
    {
        Widgets.erase(FoundWidget);
        bRemoved = true;
    }

    if (FoundShowWidget != ShowWidgets.cend())
    {
        ShowWidgets.erase(FoundShowWidget);
        bRemoved = true;
    }

    return bRemoved;
}

void HUD::AddToViewport(UIObject* Widget)
{
    if (Widget)
    {
        auto WidgetToShow = GetWidget(Widget);
        if (WidgetToShow)
        {
            ShowWidgets.emplace_back(WidgetToShow);
        }
    }
}
