#pragma once
#include <raylib.h>

#include "../ActorComponent.h"

class CameraComponent
    : public ActorComponent
{
public:
    CameraComponent(class Actor* NewOwner);
    virtual ~CameraComponent() override = default;
    
    void Update(float DeltaTime) override;
    
    void UpdateOffset(const Vector2& NewOffset);
    void UpdateZoom(float NewZoom);
    void UpdateRotation(float NewRotation);

    void AddOffset(const Vector2& NewOffset);
    void AddZoom(float NewZoom);
    void AddRotation(float NewRotation);

    Camera2D GetCamera() const { return Camera; }
    
protected:
    Camera2D Camera;
};
