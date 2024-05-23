#include "LevelBorder.h"

#include "../../../../Core/Directory/Directory.h"
#include "../../../../Core/UI/Image/UIImage.h"
#include "../../../../Core/UI/Text/UIText.h"
#include "../../../Interface/Level/Ilevel.h"

LevelBorder::LevelBorder(Object* Owner, const Slot& LayoutSlot, UIBase* Parent)
    : UIBase(Owner, LayoutSlot, Parent)
{
}

void LevelBorder::Awake()
{
    std::shared_ptr<UIImage> Border = std::make_shared<UIImage>(GetOwner(), GetLayoutSlot(), this, "LevelBorder.png");
    AddChild(Border);

    ResourceAllocator<FontResource>* FontAllocator = GetOwner()->GetContext()->FontAllocator;
    const int RobotoRegularID = FontAllocator->Add(Directory::GetInstance().GetFont("Roboto-Regular.ttf"));

    const Ilevel* InterfaceLevel = dynamic_cast<Ilevel*>(GetOwner());

    TextSettings ButtonTextSettings
    {
        FontAllocator->Get(RobotoRegularID)->Get_Impl(),
        std::to_string(InterfaceLevel->GetLevel()),
        Vector2{0.0f, 0.0f},
        0.0f,
        24.0f,
        1.0f,
        WHITE
    };

    const Slot& PopUpSlot = GetLayoutSlot();

    LevelText = std::make_shared<UIText>(
        GetOwner(), Slot{Padding{0.0f}, Crop{0.0f}, PopUpSlot.SlotRect},
        Border.get(), ButtonTextSettings);
    AddChild(LevelText);

    UIBase::Awake();
}

void LevelBorder::UpdateLevel() const
{
    const Ilevel* InterfaceLevel = dynamic_cast<Ilevel*>(GetOwner());
    LevelText->UpdateText(std::to_string(InterfaceLevel->GetLevel()));
}
