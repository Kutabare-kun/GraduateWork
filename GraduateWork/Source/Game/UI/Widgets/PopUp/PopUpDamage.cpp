#include "PopUpDamage.h"

#include "../../../../Core/Directory/Directory.h"
#include "../../../../Core/Timer/Manager/TimerManager.h"
#include "../../../../Core/UI/Text/UIText.h"

PopUpDamage::PopUpDamage(Object* Owner, const Slot& LayoutSlot, UIBase* Parent, float Damage)
    : UIBase(Owner, LayoutSlot, Parent), Damage(Damage)
{
    SetName(TextFormat("PopUpDamage: %f", Damage));
}

void PopUpDamage::Awake()
{
    ResourceAllocator<FontResource>* FontAllocator = GetOwner()->GetContext()->FontAllocator;
    const int RobotoRegularID = FontAllocator->Add(Directory::GetInstance().GetFont("Roboto-Regular.ttf"));

    const int TextDamage = static_cast<int>(std::ceil(std::fabsf(Damage)));

    TextSettings ButtonTextSettings
    {
        FontAllocator->Get(RobotoRegularID)->Get_Impl(),
        std::to_string(TextDamage),
        Vector2{0.0f, 0.0f},
        0.0f,
        48.0f,
        1.0f,
        WHITE
    };

    const Slot& PopUpSlot = GetLayoutSlot();

    DamageText = std::make_shared<UIText>(
        GetOwner(), Slot{Padding{0.0f}, Crop{0.0f}, PopUpSlot.SlotRect},
        nullptr, ButtonTextSettings);
    AddChild(DamageText);

    UIBase::Awake();

    GetOwner()->GetContext()->TimerManagerSys->AddTimer([&]()
    {
        QueueForRemoval();
    }, 1.0f);
}

void PopUpDamage::Update(float DeltaTime)
{
    UIBase::Update(DeltaTime);

    const Slot& TextLayout = DamageText->GetLayoutSlot();
    DamageText->SetLayoutSlot(Slot{
        Padding{0.0f, 0.0f, 0.0f, TextLayout.ObjectPadding.Bottom + (DeltaTime * Speed)},
        TextLayout.ObjectCrop,
        TextLayout.SlotRect
    });
}

void PopUpDamage::Draw()
{
    BeginMode2D(*GetOwner()->GetContext()->Camera);
    UIBase::Draw();
    EndMode2D();
}
