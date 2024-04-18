#pragma once
#include "../../../../Core/UI/Button/Button.h"
#include "../../../../Core/UI/Panel/Panel.h"

class WidgetGameUI
    : public Panel
{
public:
    WidgetGameUI(Object* Owner, const Rectangle& Bounds, UIObject* Parent = nullptr, Alignment HorizontalAlignment = Alignment::None);

    void Awake() override;

    void Update(float DeltaTime) override;

    void Draw() override;

private:
    std::shared_ptr<UIObject> ButtonClose;
};
