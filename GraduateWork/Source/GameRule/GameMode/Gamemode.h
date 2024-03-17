#pragma once

#include "../../Pattern/Singleton.h"

class Gamemode : public Singleton<Gamemode>
{
public:
    virtual ~Gamemode() = default;

    virtual void InitGame();

    virtual void StartGame();

    virtual void EndGame();

    class Gamestate& GetGameState() const;
};
