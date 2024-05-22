#pragma once
#include "../UIBase/UIBase.h"

class UIImage;

class UIBar
    : public UIBase
{
public:
    UIBar(Object* Owner, const Slot& LayoutSlot, UIBase* Parent, const std::string& BackgroundImageName,
             const std::string& ForegroundImageName);

    void Awake() override;

    void Update(float DeltaTime) override;

    void Draw() override;

    void UpdatePercentage(float NewPercentage);

protected:
    float Percentage = 1.0f;

    std::shared_ptr<UIImage> BackgroundImage;
    std::shared_ptr<UIImage> ForegroundImage;
};
