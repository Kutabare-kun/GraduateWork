#include "UIButton.h"

#include "../../Directory/Directory.h"

UIButton::UIButton(Object* Owner, const Slot& LayoutSlot, UIBase* Parent, ButtonStateTexture& ButtonStateTextures)
    : UIBase(Owner, LayoutSlot, Parent)
{
    SetName(TextFormat("Button %s", ButtonStateTextures.NormalFile.c_str()));

    auto TextureAllocator = GetOwner()->GetContext()->TextureAllocator;
    const Directory& DirectorySys = Directory::GetInstance();

    const int ButtonNormal = TextureAllocator->Add(DirectorySys.GetTexture(std::move(ButtonStateTextures.NormalFile)));
    ButtonTextures.emplace(ButtonState::Normal, TextureAllocator->Get(ButtonNormal));

    const int ButtonClicked = TextureAllocator->
        Add(DirectorySys.GetTexture(std::move(ButtonStateTextures.PressedFile)));
    ButtonTextures.emplace(ButtonState::Pressed, TextureAllocator->Get(ButtonClicked));

    const int ButtonHovered = TextureAllocator->
        Add(DirectorySys.GetTexture(std::move(ButtonStateTextures.HoveredFile)));
    ButtonTextures.emplace(ButtonState::Hovered, TextureAllocator->Get(ButtonHovered));

    const int ButtonDisabled = TextureAllocator->Add(
        DirectorySys.GetTexture(std::move(ButtonStateTextures.DisabledFile)));
    ButtonTextures.emplace(ButtonState::Disabled, TextureAllocator->Get(ButtonDisabled));
}

void UIButton::Awake()
{
    UIBase::Awake();

    ButtonText = GetChild<UIText>();
}

void UIButton::UpdateText()
{
    if (ButtonText)
    {
        switch (CurrentState)
        {
        case ButtonState::Normal:
            {
                const Slot& ThisSlot = ButtonText->GetLayoutSlot();
                ButtonText->SetLayoutSlot(Slot{
                        Padding{
                            ThisSlot.ObjectPadding.Left, ThisSlot.ObjectPadding.Right,
                            0.0f, ThisSlot.ObjectPadding.Bottom
                        },
                        ThisSlot.ObjectCrop,
                        ThisSlot.SlotRect
                    }
                );
            }
            break;
        case ButtonState::Hovered:
            {
                const Slot& ThisSlot = ButtonText->GetLayoutSlot();
                ButtonText->SetLayoutSlot(Slot{
                        Padding{
                            ThisSlot.ObjectPadding.Left, ThisSlot.ObjectPadding.Right,
                            5.0f, ThisSlot.ObjectPadding.Bottom
                        },
                        ThisSlot.ObjectCrop,
                        ThisSlot.SlotRect
                    }
                );
            }
            break;
        }
    }
}

void UIButton::Update(float DeltaTime)
{
    UIBase::Update(DeltaTime);

    if (!IsVisible() || !GetParent()->IsVisible()) return;

    if (CurrentState == ButtonState::Disabled) return;

    if (CurrentState == ButtonState::Pressed && !IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        Action();
    }

    if (const Vector2& MousePosition = GetMousePosition();
        CheckCollisionPointRec(MousePosition, GetBounds()))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) CurrentState = ButtonState::Pressed;
        else
        {
            CurrentState = ButtonState::Hovered;
            UpdateText();
        }
    }
    else
    {
        CurrentState = ButtonState::Normal;
        UpdateText();
    }
}

void UIButton::Draw()
{
    if (!IsVisible()) return;

    DrawTexturePro(ButtonTextures[CurrentState]->Get_Impl(),
                   {
                       0, 0,
                       (float)ButtonTextures[CurrentState]->Get_Impl().width,
                       (float)ButtonTextures[CurrentState]->Get_Impl().height
                   },
                   GetBounds(), {0, 0}, 0, WHITE);

    UIBase::Draw();
}
