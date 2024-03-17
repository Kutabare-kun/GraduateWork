#pragma once
#include "../Actor.h"

class Obstacle : public Actor
{
public:
    Obstacle(const std::string& TexturePath, Vector2 Posisiton);

    void BeginPlay() override;

    void EventTick(float DeltaTime) override;

    void EndPlay() override;

    void Draw() const override;
};
