#pragma once

class Scene
{
public:
    virtual ~Scene() = default;

    virtual void OnCreate()
    {
    }

    virtual void OnDestroy()
    {
    }

    virtual void OnActivate()
    {
    }

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
