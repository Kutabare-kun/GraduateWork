#pragma once
#include <list>
#include <memory>
#include <string>

#include "../Pattern/Singleton.h"

extern const std::string CurrentPath;

class Actor;

class World final
    : public Singleton<World>
{
public:
    // CreateActor is a factory method that creates an actor and adds it to the world
    template <typename Type, typename... Args>
    static std::shared_ptr<Type> CreateActor(Args&&... args)
    {
        auto NewActor = std::make_shared<Type>(std::forward<Args>(args)...);
        World::GetInstance().AddActor(NewActor);
        return NewActor;
    }

    // CreateObstacle is a factory method that creates an obstacle and adds it to the world
    template <typename Type, typename... Args>
    static std::shared_ptr<Type> CreateObstacle(Args&&... args)
    {
        auto NewObstacle = std::make_shared<Type>(std::forward<Args>(args)...);
        World::GetInstance().AddObstacle(NewObstacle);
        return NewObstacle;
    }

public:
    ~World() = default;

    // Initialize the world
    void InitWorld();

    class Gamemode& GetGameMode() const;

    // Remove Actor in the next frame
    void RemoveActorNextFrame(Actor* VictimActor);

    // Remove Obstacle in the next frame
    void RemoveObstacleNextFrame(Actor* VictimObstacle);

    // Called when the world is created
    void EventTick(float DeltaTime);

    // Called when the world is destroyed
    void EventEnd();

    // Draw the world
    void Draw() const;

    const std::list<std::shared_ptr<Actor>>& GetObstacles() const;
    const std::list<std::shared_ptr<Actor>>& GetActors() const;

protected:
    // Clear the world
    void Clear();

    void AddObstacle(std::shared_ptr<Actor> NewObstacle);
    void AddActor(std::shared_ptr<Actor> NewActor);

protected:
    std::list<std::shared_ptr<Actor>> Obstacles;
    std::list<std::shared_ptr<Actor>> Actors;

    std::list<std::shared_ptr<Actor>> RemoveActorsNextFrame;
    std::list<std::shared_ptr<Actor>> RemoveObstaclesNextFrame;
};
