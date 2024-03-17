#include "Gamemode.h"
#include "../GameState/Gamestate.h"

void Gamemode::InitGame()
{
}

void Gamemode::StartGame()
{
}

void Gamemode::EndGame()
{
}

Gamestate& Gamemode::GetGameState() const
{
    return Gamestate::GetInstance();
}
