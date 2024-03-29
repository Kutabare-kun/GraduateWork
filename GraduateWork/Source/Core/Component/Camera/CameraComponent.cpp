#include "CameraComponent.h"

#include <raymath.h>

#include "../../Object/Actor/Actor.h"
#include "../../StaticFunctions/Debug.h"
#include "../../Window/Window.h"

CameraComponent::CameraComponent(class Actor* NewOwner)
    : ActorComponent(NewOwner, true),
    Camera({})
{
    Vector2 ScreenSize = Window::GetInstance().GetScreenSize();
    Camera.offset = {ScreenSize.x / 2.0f, ScreenSize.y / 2.0f};
    Camera.zoom = 1.0f;
}

void CameraComponent::Update(float DeltaTime)
{
    ActorComponent::Update(DeltaTime);

    Rectangle Rect = static_cast<Actor*>(GetOwner())->GetActorRectangle();
    Camera.target = {Rect.x, Rect.y};
}

void CameraComponent::UpdateOffset(const Vector2& NewOffset)
{
    Camera.offset = NewOffset;
}

void CameraComponent::UpdateZoom(float NewZoom)
{
    Debug::GetInstance().Log(TextFormat("Camera Zoom: Before %f, After %f", Camera.zoom, NewZoom));
    Camera.zoom = NewZoom;
}

void CameraComponent::UpdateRotation(float NewRotation)
{
    Camera.rotation = NewRotation;
}

void CameraComponent::AddOffset(const Vector2& NewOffset)
{
    Camera.offset.x += NewOffset.x;
    Camera.offset.y += NewOffset.y;
}

void CameraComponent::AddZoom(float NewZoom)
{
    UpdateZoom(Clamp(Camera.zoom + NewZoom, 0.1f, 2.0f));
}

void CameraComponent::AddRotation(float NewRotation)
{
    Camera.rotation += NewRotation;
}
