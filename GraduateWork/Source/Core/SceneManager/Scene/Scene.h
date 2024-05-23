#pragma once
#include <memory>

class Scene
{
public:
    virtual ~Scene() = default;

    // Called when scene initially created. Called once.
    virtual void OnCreate()
    {
    }

    // Called when scene destroyed. Called at most once (if a scene 
    // is not removed from the game, this will never be called).
    virtual void OnDestroy()
    {
    }

    // Called whenever a scene is transitioned into. Can be 
    // called many times in a typical game cycle.
    virtual void OnActivate()
    {
    }

    // Called whenever a transition out of a scene occurs. 
    // Can be called many times in a typical game cycle.
    virtual void OnDeactivate()
    {
    }

    virtual void ProcessInput()
    {
    }

    virtual void Update(float DeltaTime)
    {
    }

    virtual void LateUpdate(float DeltaTime)
    {
    }

    virtual void Draw()
    {
    }
};
