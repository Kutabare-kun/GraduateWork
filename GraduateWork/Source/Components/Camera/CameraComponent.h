#pragma once
#include <raylib.h>

#include "../../Core/Component/ActorComponent.h"

extern const int ScreenWidth;
extern const int ScreenHeight;

class CameraComponent
    : public ActorComponent
{
public:
    CameraComponent(class Actor* NewOwner, Vector2 Target, float Zoom = 1.0f, float Rotation = 0.0f);
    virtual ~CameraComponent() override = default;
    
    virtual void EventTick(float DeltaTime) override;
    
    void UpdateOffset(const Vector2& NewOffset);
    void UpdateZoom(float NewZoom);
    void UpdateRotation(float NewRotation);

    Camera2D GetCamera() const { return Camera; }
    
protected:
    Camera2D Camera;
};
