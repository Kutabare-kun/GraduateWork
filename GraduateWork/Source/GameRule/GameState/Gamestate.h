#pragma once
#include "../../Actors/Player/Player.h"
#include "../../Pattern/Singleton.h"

class Gamestate : public Singleton<Gamestate>
{
public:
    virtual void InitGame();

    virtual void EndGame();

    Actor* GetPlayer() const;

    template <typename Type>
    Type* GetPlayer() const
    {
        return dynamic_cast<Type*>(PlayerActor.get());
    }

private:
    std::shared_ptr<Actor> PlayerActor;
};
