#pragma once
#include "../UIObject.h"
#include "../../Object/Object.h"
#include "../Button/Button.h"
#include "../Panel/Panel.h"
#include "../../../Game/UI/Widget/GameUI/WidgetGameUI.h"

class HUD
{
public:
    template<typename Type = UIObject>
    std::shared_ptr<Type> AddWidget(Object* Owner, const Rectangle& Bounds, UIObject* Parent = nullptr, Alignment HorizontalAlignment = Alignment::None)
    {
        std::shared_ptr<Type> Widget = std::make_shared<Type>(Owner, Bounds, Parent, HorizontalAlignment);
        
        auto WidgetPtr = std::dynamic_pointer_cast<UIObject>(Widget);
        Widgets.push_back(WidgetPtr);
        
        return Widget;
    }

    template<typename Type>
    std::shared_ptr<Type> GetWidget() const
    {
        for (auto& ExistingWidget : Widgets)
        {
            if (auto Widget = std::dynamic_pointer_cast<Type>(ExistingWidget); Widget)
            {
                return Widget;
            }
        }

        return nullptr;
    }

    template<typename Type>
    bool RemoveWidgetByClass()
    {
        for (auto Iter = Widgets.begin(); Iter != Widgets.end();)
        {
            if (auto Widget = std::dynamic_pointer_cast<Type>(*Iter); Widget)
            {
                Iter = Widgets.erase(Iter);
                return true;
            }
            else
            {
                ++Iter;
            }
        }

        return false;
    }
    
public:
    HUD(Object* Owner);
    virtual ~HUD() = default;

    virtual void Awake();
    
    virtual void Draw();

    virtual void Update(float DeltaTime);

    std::shared_ptr<UIObject> GetWidget(UIObject* Widget);

    bool RemoveWidget(std::shared_ptr<UIObject> Widget);
    
    Object* GetOwner() const { return Owner; }

protected:
    void AddToViewport(UIObject* Widget);

private:
    Object* Owner;

    std::vector<std::shared_ptr<UIObject>> Widgets;
    std::vector<std::shared_ptr<UIObject>> ShowWidgets;

public:
    friend UIObject;
};
