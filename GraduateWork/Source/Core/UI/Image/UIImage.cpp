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

    DrawTexturePro(ImageTexture->Get_Impl(),
                   {
                       0, 0,
                       (float)ImageTexture->Get_Impl().width,
                       (float)ImageTexture->Get_Impl().height
                   },
                   GetBounds(), {0, 0}, 0, WHITE);
}
