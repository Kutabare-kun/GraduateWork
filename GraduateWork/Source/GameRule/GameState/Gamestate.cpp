#include "Gamestate.h"

#include "../../Actors/Player/Player.h"
#include "../../Core/Directory/Directory.h"
#include "../../World/World.h"

void Gamestate::InitGame()
{
    PlayerActor = World::GetInstance().CreateActor<Player>(Directory::GetInstance().GetTexture("Player.png"),
                                                           Vector2{200, 200});
}

void Gamestate::EndGame()
{
}

Actor* Gamestate::GetPlayer() const
{
    return PlayerActor.get();
}
