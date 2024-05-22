#include "UIImage.h"

#include "../../Directory/Directory.h"

UIImage::UIImage(Object* Owner, const Slot& LayoutSlot, UIBase* Parent, const std::string& ImageName)
    : UIBase(Owner, LayoutSlot, Parent)
{
    auto TextureAllocator = GetOwner()->GetContext()->TextureAllocator;
    const Directory& DirectorySys = Directory::GetInstance();

    const int IDImage = TextureAllocator->Add(DirectorySys.GetTexture(std::move(ImageName)));
    ImageTexture = TextureAllocator->Get(IDImage);
}

void UIImage::Draw()
{
    UIBase::Draw();

    if (!IsVisible()) return;

    const Slot& ImageLayout = GetLayoutSlot();

    DrawTexturePro(ImageTexture->Get_Impl(),
                   {
                       ImageLayout.ObjectCrop.CropRect.x, ImageLayout.ObjectCrop.CropRect.y,
                       (float)ImageTexture->Get_Impl().width - ImageLayout.ObjectCrop.CropRect.width,
                       (float)ImageTexture->Get_Impl().height - ImageLayout.ObjectCrop.CropRect.height
                   },
                   GetBounds(), {
                       ImageLayout.ObjectPadding.Right - ImageLayout.ObjectPadding.Left,
                       ImageLayout.ObjectPadding.Bottom - ImageLayout.ObjectPadding.Top
                   }, 0, WHITE);
}

Rectangle UIImage::GetTextureBounds() const
{
    return {
        0, 0,
        (float)ImageTexture->Get_Impl().width,
        (float)ImageTexture->Get_Impl().height
    };
}
