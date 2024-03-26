#include "SceneStateMachine.h"

#include "Scene/Scene.h"

void SceneStateMachine::ProcessInput()
{
    if (CurrentScene) CurrentScene->ProcessInput();
}

void SceneStateMachine::Update(float DeltaTime)
{
    if (CurrentScene) CurrentScene->Update(DeltaTime);
}

void SceneStateMachine::LateUpdate(float DeltaTime)
{
    if (CurrentScene) CurrentScene->LateUpdate(DeltaTime);
}

void SceneStateMachine::Draw()
{
    if (CurrentScene) CurrentScene->Draw();
}

unsigned SceneStateMachine::Add(std::shared_ptr<Scene> NewScene)
{
    auto Inserted = Scenes.insert(std::make_pair(InsertedSceneId, NewScene));

    ++InsertedSceneId;

    Inserted.first->second->OnCreate();

    return InsertedSceneId - 1;
}

void SceneStateMachine::SwitchTo(unsigned Id)
{
    auto Iter = Scenes.find(Id);

    if (Iter != Scenes.end())
    {
        if (CurrentScene)
        {
            CurrentScene->OnDeactivate();
        }

        CurrentScene = Iter->second;
        CurrentScene->OnActivate();
    }
}

void SceneStateMachine::Remove(unsigned Id)
{
    auto Iter = Scenes.find(Id);

    if (Iter != Scenes.end())
    {
        if (CurrentScene == Iter->second)
        {
            //CurrentScene->OnDeactivate();
            CurrentScene = nullptr;
        }

        Iter->second->OnDestroy();
        Scenes.erase(Iter);
    }
}
