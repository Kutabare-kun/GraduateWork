#pragma once
#include "../../../../Core/UI/UIBase/UIBase.h"

class PopUpDamage
    : public UIBase
{
public:
    PopUpDamage(Object* Owner, const Slot& LayoutSlot, UIBase* Parent = nullptr, float Damage = 0.0f);

    void Awake() override;

    void Update(float DeltaTime) override;

    void Draw() override;

private:
    std::shared_ptr<UIText> DamageText;

    float Damage;
    float Speed = 100.0f;
};
