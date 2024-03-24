#include "CameraComponent.h"

#include "../../Actors/Actor.h"

CameraComponent::CameraComponent(class Actor* NewOwner, Vector2 Target, float Zoom, float Rotation)
    : ActorComponent(NewOwner, true),
    Camera({})
{
    Camera.target = Target;
    Camera.offset = {ScreenWidth / 2.0f, ScreenHeight / 2.0f};
    Camera.rotation = Rotation;
    Camera.zoom = Zoom;
}

void CameraComponent::EventTick(float DeltaTime)
{
    Rectangle Rect = GetOwner()->GetActorRectangle();
    Camera.target = {Rect.x + Rect.width / 2.0f, Rect.y + Rect.height / 2.0f};
}

void CameraComponent::UpdateOffset(const Vector2& NewOffset)
{
    Camera.offset = NewOffset;
}

void CameraComponent::UpdateZoom(float NewZoom)
{
    Camera.zoom = NewZoom;
}

void CameraComponent::UpdateRotation(float NewRotation)
{
    Camera.rotation = NewRotation;
}
