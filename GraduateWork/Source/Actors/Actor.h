#pragma once
#include <memory>
#include <raylib.h>
#include <string>

#include "../Core/Object/Object.h"
#include "../SmartPtr/SmartTexture.h"

class Actor
    : public Object
{
public:
    // Constructor
    Actor(const std::string& TexturePath, Vector2 Posisiton, bool bEnableTicks = true);

    // Destructor
    virtual ~Actor() = default;

    // Calling after constructor
    virtual void BeginPlay() = 0;

    void EventTick(float DeltaTime) override = 0;

    // Calling before destructor
    virtual void EndPlay() = 0;

    virtual void Draw() const;

    // Return position of actor
    Vector2& GetActorPosition();

    // Return position of actor
    const Vector2& GetActorPosition() const;

    // Return rectangle of actor
    Rectangle GetActorRectangle();

    // Return rectangle of actor
    const Rectangle GetActorRectangle() const;

    void SetActorPosition(const Vector2& NewPosition);

private:
    std::unique_ptr<SmartTexture> ActorTexture;
    Vector2 Position;
};
