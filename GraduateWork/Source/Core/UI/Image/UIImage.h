#pragma once
#include "../UIBase/UIBase.h"

class UIImage
    : public UIBase
{
public:
    UIImage(Object* Owner, const Slot& LayoutSlot, UIBase* Parent, const std::string& ImageName);

    void Awake() override;

    void Update(float DeltaTime) override;

    void Draw() override;

private:
    std::shared_ptr<TextureResource> ImageTexture;
};
