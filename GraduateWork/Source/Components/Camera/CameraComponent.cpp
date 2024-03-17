#include "CameraComponent.h"

#include "../../Actors/Actor.h"

CameraComponent::CameraComponent()
    : Camera({})
{
    Camera.target = {};
    Camera.offset = {};
    Camera.rotation = 0.0f;
    Camera.zoom = 1.0f;
}

CameraComponent::CameraComponent(Vector2 Target, float Zoom, float Rotation)
    : Camera({})
{
    Camera.target = Target;
    Camera.offset = {ScreenWidth / 2.0f, ScreenHeight / 2.0f};
    Camera.rotation = Rotation;
    Camera.zoom = Zoom;
}

void CameraComponent::AttachTo(Actor* NewOwner)
{
    Owner = NewOwner;
}

void CameraComponent::UpdateCamera()
{
    Camera.target = Owner->GetActorPosition();
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
