#pragma once
#include "../UIBase/UIBase.h"

class UIImage
    : public UIBase
{
public:
    UIImage(Object* Owner, const Slot& LayoutSlot, UIBase* Parent, const std::string& ImageName);

    void Draw() override;

    Rectangle GetTextureBounds() const;

private:
    std::shared_ptr<TextureResource> ImageTexture;
};
