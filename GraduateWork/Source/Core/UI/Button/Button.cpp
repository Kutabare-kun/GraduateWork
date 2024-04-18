#include "Button.h"

Button::Button(Object* Owner, const Rectangle& Bounds, UIObject* Parent,
               Alignment HorizontalAlignment)
    : UIObject(Owner, Bounds, Parent, HorizontalAlignment)
{
}

void Button::Awake()
{
    UIObject::Awake();
}

void Button::Update(float DeltaTime)
{
    UIObject::Update(DeltaTime);

    const Vector2 MousePosition = GetMousePosition();
    const Rectangle& ButtonBounds = GetRelativeBounds();

    if (CheckCollisionPointRec(MousePosition, ButtonBounds))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // State Pressed

            if (OnClicked)
            {
                OnClicked();
            }

            return;
        }

        // State Hovered
    }
}

void Button::Draw()
{
    if (IsAttached() && GetObjectAlignment() == Alignment::Full)
        DrawTexturePro(ButtonTexture->Get_Impl(),
                       Rectangle{0.0f, 0.0f, static_cast<float>(ButtonTexture->Get_Impl().width), static_cast<float>(ButtonTexture->Get_Impl().height)},
                       Rectangle{ GetParentRelativeBounds().x, GetParentRelativeBounds().y,
                           GetParentRelativeBounds().width, GetParentRelativeBounds().height
                       }, Vector2{0.0f, 0.0f}, 0, WHITE);
    else
        DrawTexturePro(ButtonTexture->Get_Impl(),
                       Rectangle{0, 0, static_cast<float>(ButtonTexture->Get_Impl().width), static_cast<float>(ButtonTexture->Get_Impl().height)},
                       Rectangle{ GetRelativeBounds().x, GetRelativeBounds().y,
                           GetRelativeBounds().width, GetRelativeBounds().height
                       }, Vector2{0, 0}, 0, WHITE);
}

void Button::AttachOnClicked(OnEvent&& Event)
{
    OnClicked = Event;
}

void Button::SetTexture(int TextureID)
{
    SharedContext* Context = GetOwner()->GetContext();
    ButtonTexture = Context->TextureAllocator->Get(TextureID);
}
