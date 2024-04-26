#include "UIButton.h"

#include "../../Directory/Directory.h"

UIButton::UIButton(Object* Owner, const Slot& LayoutSlot, UIBase* Parent)
    : UIBase(Owner, LayoutSlot, Parent)
{
}

void UIButton::Awake()
{
    UIBase::Awake();

    auto TextureAllocator = GetOwner()->GetContext()->TextureAllocator;
    const Directory& DirectorySys = Directory::GetInstance();

    const int ButtonNormal = TextureAllocator->Add(DirectorySys.GetTexture("Button_Normal.png"));
    ButtonTextures.emplace(ButtonState::Normal, TextureAllocator->Get(ButtonNormal));

    const int ButtonClicked = TextureAllocator->Add(DirectorySys.GetTexture("Button_Clicked.png"));
    ButtonTextures.emplace(ButtonState::Pressed, TextureAllocator->Get(ButtonClicked));
    ButtonTextures.emplace(ButtonState::Hovered, TextureAllocator->Get(ButtonClicked));
    ButtonTextures.emplace(ButtonState::Disabled, TextureAllocator->Get(ButtonClicked));
}

void UIButton::Update(float DeltaTime)
{
    UIBase::Update(DeltaTime);

    if (CurrentState == ButtonState::Disabled) return;

    if (CurrentState == ButtonState::Pressed && !IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        Action();
    }

    if (const Vector2& MousePosition = GetMousePosition();
        CheckCollisionPointRec(MousePosition, GetBounds()))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) CurrentState = ButtonState::Pressed;
        else CurrentState = ButtonState::Hovered;
    }
    else
    {
        CurrentState = ButtonState::Normal;
    }
}

void UIButton::Draw()
{
    UIBase::Draw();

    DrawTexturePro(ButtonTextures[CurrentState]->Get_Impl(),
                   {
                       0, 0,
                       (float)ButtonTextures[CurrentState]->Get_Impl().width,
                       (float)ButtonTextures[CurrentState]->Get_Impl().height
                   },
                   GetBounds(), {0, 0}, 0, WHITE);
}
