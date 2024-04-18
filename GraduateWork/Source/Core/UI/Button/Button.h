#pragma once
#include <functional>

#include "../UIObject.h"

enum class ButtonState
{
    Normal,
    Clicked
};

using OnEvent = std::function<void(void)>;

class Button
    : public UIObject
{
public:
    Button(Object* Owner, const Rectangle& Bounds, UIObject* Parent = nullptr, Alignment HorizontalAlignment = Alignment::None);
    ~Button() override = default;

    void Awake() override;

    void Update(float DeltaTime) override;

    void Draw() override;

    void AttachOnClicked(OnEvent&& Event);

    void SetTexture(int TextureID, ButtonState State);

    void SetTextUI(std::shared_ptr<UIObject>& ButtonText);

private:
    OnEvent OnClicked;

    ButtonState CurrentState;

    std::map<ButtonState, std::shared_ptr<TextureResource>> ButtonTextures;

    std::shared_ptr<UIObject> ButtonText;
};
