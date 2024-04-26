#pragma once
#include <functional>

#include "../UIBase/UIBase.h"

enum class ButtonState
{
    Normal,
    Hovered,
    Pressed,
    Disabled
};

using ButtonAction = std::function<void()>;

class UIButton
    : public UIBase
{
public:
    UIButton(Object* Owner, const Slot& LayoutSlot, UIBase* Parent);
    
    void Awake() override;

    void Update(float DeltaTime) override;

    void Draw() override;

    void SetAction(const ButtonAction&& NewAction) { Action = NewAction; }

private:
    std::map<ButtonState, std::shared_ptr<TextureResource>> ButtonTextures;

    ButtonState CurrentState = ButtonState::Normal;

    ButtonAction Action;
};
