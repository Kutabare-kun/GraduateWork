#include "Gamemode.h"

#include "../../Constructor/Constructor.h"
#include "../../World/World.h"
#include "../GameState/Gamestate.h"
#include "../../Actors/Obstacle/Obstacle.h"

void Gamemode::InitGame()
{
    auto Grid = Constructor::ReadMap(CurrentPath + R"(\Resource\Maps\Map_1.csv)");
    for (size_t Row = 0; Row < Grid.size(); ++Row)
    {
        for (size_t Column = 0; Column < Grid[Row].size(); ++Column)
        {
            if (Grid[Row][Column])
            {
                World::GetInstance().CreateObstacle<Obstacle>(CurrentPath + R"(\Resource\Texture\Obstacle.png)",
                                                              Vector2{
                                                                  static_cast<float>(Column) * 64.0f,
                                                                  static_cast<float>(Row) * 64.0f
                                                              });
            }
        }
    }
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
