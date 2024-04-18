#pragma once
#include <functional>

#include "../UIObject.h"

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

    void SetTexture(int TextureID);

private:
    OnEvent OnClicked;

    std::shared_ptr<TextureResource> ButtonTexture;
};
