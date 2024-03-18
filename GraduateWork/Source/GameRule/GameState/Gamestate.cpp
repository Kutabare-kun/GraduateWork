#include "Gamestate.h"

#include "../../Actors/Player/Player.h"
#include "../../World/World.h"

void Gamestate::InitGame()
{
    PlayerActor = World::GetInstance().CreateActor<Player>(CurrentPath + R"(\Resource\Texture\Player.png)",
                                                           Vector2{200, 200});
}

void Gamestate::EndGame()
{
}

Actor* Gamestate::GetPlayer() const
{
    return PlayerActor.get();
}
