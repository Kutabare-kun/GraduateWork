#pragma once

#include "../Actor.h"
#include "../../Components/Camera/CameraComponent.h"
#include "../../Components/Movement/MovementComponent.h"

class Player
    : public Actor
{
public:
    Player(const std::string& TexturePath, Vector2 Posisiton);
    
    void BeginPlay() override;
    void Move(float DeltaTime);

    void EventTick(float DeltaTime) override;

    void EndPlay() override;

    void Draw() const override;

    CameraComponent* GetCameraComponent() const { return CameraComp.get(); }
    MovementComponent* GetMovementComponent() const { return MovementComp.get(); }

    Camera2D GetCamera() const { return CameraComp->GetCamera(); }

protected:
    std::shared_ptr<MovementComponent> MovementComp;
    std::shared_ptr<CameraComponent> CameraComp;
};
