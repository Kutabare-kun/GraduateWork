#include "Button.h"

Button::Button(Object* Owner, const Rectangle& Bounds, UIObject* Parent,
               Alignment HorizontalAlignment)
    : UIObject(Owner, Bounds, Parent, HorizontalAlignment),
      CurrentState(ButtonState::Normal),
      ButtonText(nullptr)
{
}

void Button::Awake()
{
    UIObject::Awake();

    ButtonText->Awake();
}

void Button::Update(float DeltaTime)
{
    UIObject::Update(DeltaTime);

    ButtonText->Update(DeltaTime);

    const Vector2 MousePosition = GetMousePosition();
    const Rectangle& ButtonBounds = GetRelativeBounds();

    if (CheckCollisionPointRec(MousePosition, ButtonBounds))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (OnClicked)
            {
                OnClicked();
            }

            return;
        }

        // State Hovered
        CurrentState = ButtonState::Clicked;

        return;
    }

    CurrentState = ButtonState::Normal;
}

void Button::Draw()
{
    if (IsAttached() && GetObjectAlignment() == Alignment::Full)
        DrawTexturePro(ButtonTextures[CurrentState]->Get_Impl(),
                       Rectangle{
                           0.0f, 0.0f, static_cast<float>(ButtonTextures[CurrentState]->Get_Impl().width),
                           static_cast<float>(ButtonTextures[CurrentState]->Get_Impl().height)
                       },
                       GetParentRelativeBounds(),
                       Vector2{0.0f, 0.0f}, 0, WHITE);
    else
        DrawTexturePro(ButtonTextures[CurrentState]->Get_Impl(),
                       Rectangle{
                           0, 0, static_cast<float>(ButtonTextures[CurrentState]->Get_Impl().width),
                           static_cast<float>(ButtonTextures[CurrentState]->Get_Impl().height)
                       },
                       GetRelativeBounds(),
                       Vector2{0, 0}, 0, WHITE);

    ButtonText->Draw();
}

void Button::AttachOnClicked(OnEvent&& Event)
{
    OnClicked = Event;
}

void Button::SetTexture(int TextureID, ButtonState State)
{
    SharedContext* Context = GetOwner()->GetContext();
    ButtonTextures.emplace(State, Context->TextureAllocator->Get(TextureID));
}

void Button::SetTextUI(std::shared_ptr<UIObject>& ButtonText)
{
    this->ButtonText = ButtonText;
    this->ButtonText->AttachTo(this);
}
