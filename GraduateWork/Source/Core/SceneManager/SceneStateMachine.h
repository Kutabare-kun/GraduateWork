#pragma once
#include <memory>
#include <unordered_map>

#include "../Pattern/Singleton.h"

class Scene;

class SceneStateMachine
    : public Singleton<SceneStateMachine>
{
public:
    template <typename Type>
    int GetScene()
    {
        for (const auto& [Key, Value] : Scenes)
        {
            if (const auto Target = std::dynamic_pointer_cast<Type>(Value); Target) return Key;
        }

        return -1;
    }

public:
    // ProcessInput, Update, LateUpdate, and Draw will simply be 
    // pass through methods. They will call the correspondingly 
    // named methods of the active scene.
    void ProcessInput();
    void Update(float DeltaTime);
    void LateUpdate(float DeltaTime);
    void Draw();

    // Adds a scene to the state machine and returns the id of that scene.
    unsigned Add(std::shared_ptr<Scene> NewScene);

    // Transitions to scene with specified id.
    void SwitchTo(unsigned int Id);

    // Removes scene from state machine.
    void Remove(unsigned int Id);

    std::shared_ptr<Scene> GetScene(unsigned int Id) { return Scenes.find(Id)->second; }

private:
    // Stores all of the scenes associated with this state machine.
    std::unordered_map<unsigned, std::shared_ptr<Scene>> Scenes;

    // Stores a reference to the current scene. Used when drawing/updating.
    std::shared_ptr<Scene> CurrentScene;

    // Stores our current scene id. This is incremented whenever 
    // a scene is added.
    unsigned int InsertedSceneId = 0;
};
