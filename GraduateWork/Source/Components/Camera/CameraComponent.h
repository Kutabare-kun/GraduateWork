#pragma once
#include <raylib.h>

extern const int ScreenWidth;
extern const int ScreenHeight;

class CameraComponent
{
public:
    CameraComponent();
    CameraComponent(Vector2 Target, float Zoom = 1.0f, float Rotation = 0.0f);
    virtual ~CameraComponent() = default;

    void AttachTo(class Actor* NewOwner);
    void UpdateCamera();
    
    void UpdateOffset(const Vector2& NewOffset);
    void UpdateZoom(float NewZoom);
    void UpdateRotation(float NewRotation);

    Camera2D GetCamera() { return Camera; }
    
protected:
    Camera2D Camera;

private:
    class Actor* Owner = nullptr;
};
