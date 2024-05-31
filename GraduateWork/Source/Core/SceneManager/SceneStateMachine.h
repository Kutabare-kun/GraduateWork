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
    void ProcessInput();
    void Update(float DeltaTime);
    void LateUpdate(float DeltaTime);
    void Draw();

    unsigned Add(std::shared_ptr<Scene> NewScene);

    void SwitchTo(unsigned int Id);

    void Remove(unsigned int Id);

    std::shared_ptr<Scene> GetScene(unsigned int Id) { return Scenes.find(Id)->second; }

private:
    std::unordered_map<unsigned, std::shared_ptr<Scene>> Scenes;

    std::shared_ptr<Scene> CurrentScene;

    unsigned int InsertedSceneId = 0;
};
