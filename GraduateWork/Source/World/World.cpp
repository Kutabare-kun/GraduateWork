#include "World.h"

#include <iostream>

#include "../Actors/Actor.h"
#include "../GameRule/GameMode/Gamemode.h"
#include "../GameRule/GameState/Gamestate.h"

void World::AddObstacle(std::shared_ptr<Actor> NewObstacle)
{
    Obstacles.push_back(NewObstacle);
    NewObstacle->BeginPlay();
}

void World::AddActor(std::shared_ptr<Actor> NewActor)
{
    Actors.push_back(NewActor);
    NewActor->BeginPlay();
}

void World::InitWorld()
{
    GetGameMode().InitGame();
    GetGameMode().GetGameState().InitGame();
}

Gamemode& World::GetGameMode() const
{
    return Gamemode::GetInstance();
}

void World::RemoveActorNextFrame(Actor* VictimActor)
{
    auto Iter = std::ranges::find_if(Actors.begin(), Actors.end(), [VictimActor](std::shared_ptr<Actor>& MyActor)
    {
        return MyActor.get() == VictimActor;
    });

    if (Iter != Actors.end())
    {
        RemoveActorsNextFrame.push_back(*Iter);
    }
}

void World::RemoveObstacleNextFrame(Actor* VictimObstacle)
{
    auto Iter = std::ranges::find_if(Obstacles.begin(), Obstacles.end(), [VictimObstacle](std::shared_ptr<Actor>& MyObstacle)
    {
        return MyObstacle.get() == VictimObstacle;
    });

    if (Iter != Obstacles.end())
    {
        RemoveObstaclesNextFrame.push_back(*Iter);
    }
}

void World::EventTick(float DeltaTime)
{
    // Remove actors and obstacles
    if (!RemoveActorsNextFrame.empty())
    {
        for (auto& RemoveActor : RemoveActorsNextFrame)
        {
            RemoveActor->EndPlay();
            Actors.remove(RemoveActor);
        }
        RemoveActorsNextFrame.clear();
    }

    if (!RemoveObstaclesNextFrame.empty())
    {
        for (auto& RemoveObstacle : RemoveObstaclesNextFrame)
        {
            RemoveObstacle->EndPlay();
            Obstacles.remove(RemoveObstacle);
        }
        RemoveObstaclesNextFrame.clear();
    }
    // ~Remove actors and obstacles

    // Generate events
    // TODO: Add events
    // ~Generate events

    // Tick actors and obstacles
    for (auto& WorldActor : Actors)
    {
        if (WorldActor->IsEnableTicks())
        {
            WorldActor->EventTick(DeltaTime);
        }
    }

    for (auto& WorldObstlace : Obstacles)
    {
        if (WorldObstlace->IsEnableTicks())
        {
            WorldObstlace->EventTick(DeltaTime);
        }
    }
    // ~Tick actors and obstacles
}

void World::EventEnd()
{
    GetGameMode().EndGame();
    GetGameMode().GetGameState().EndGame();
    
    Clear();
}

void World::Draw() const
{
    for (const auto& WorldActor : Actors)
    {
        WorldActor->Draw();
    }

    for (const auto& WorldObstacle : Obstacles)
    {
        WorldObstacle->Draw();
    }
}

void World::Clear()
{
    for (std::list<std::shared_ptr<Actor>>::iterator Iter = Actors.begin(); Iter != Actors.end();)
    {
        (*Iter)->EndPlay();
        Iter = Actors.erase(Iter);
    }

    for (std::list<std::shared_ptr<Actor>>::iterator Iter = Obstacles.begin(); Iter != Obstacles.end();)
    {
        (*Iter)->EndPlay();
        Iter = Obstacles.erase(Iter);
    }
}

const std::list<std::shared_ptr<Actor>>& World::GetObstacles() const
{
    return Obstacles;
}

const std::list<std::shared_ptr<Actor>>& World::GetActors() const
{
    return Actors;
}
