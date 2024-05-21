#pragma once
#include <functional>

#include "../UIBase/UIBase.h"

#include "../Text/UIText.h"

enum class ButtonState
{
    Normal,
    Hovered,
    Pressed,
    Disabled
};

struct ButtonStateTexture
{
    std::string NormalFile;
    std::string HoveredFile;
    std::string PressedFile;
    std::string DisabledFile;
};

using ButtonAction = std::function<void()>;

class UIButton
    : public UIBase
{
public:
    UIButton(Object* Owner, const Slot& LayoutSlot, UIBase* Parent, ButtonStateTexture& ButtonStateTextures);

    void Awake() override;

    void Update(float DeltaTime) override;

    void Draw() override;

    void SetAction(const ButtonAction&& NewAction) { Action = NewAction; }

private:
    std::map<ButtonState, std::shared_ptr<TextureResource>> ButtonTextures;

    std::shared_ptr<UIText> ButtonText;

    ButtonState CurrentState = ButtonState::Normal;

    ButtonAction Action;
};
