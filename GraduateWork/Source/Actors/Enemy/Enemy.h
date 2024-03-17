#pragma once
#include "../Actor.h"
#include "../../Components/Movement/MovementComponent.h"

class Enemy
    : public Actor
{
public:
    Enemy(const std::string& TexturePath, Vector2 Posisiton);
    
    void BeginPlay() override;

    void EventTick(float DeltaTime) override;

    void EndPlay() override;

    void Draw() const override;

protected:
    std::unique_ptr<MovementComponent> MovementComp = nullptr;
};
