#pragma once
#include <memory>
#include <vector>

#include "../System/Collider/ColliderSystem.h"
#include "../System/Drawable/DrawableSystem.h"

class Object;

class ObjectCollection
{
public:
    template <typename Type, typename... Arguments>
    std::shared_ptr<Type> CreateObject(Arguments&&... Args)
    {
        static_assert(std::is_base_of_v<Object, Type>, "Type must derive from Object");
        
        auto Obj = std::make_shared<Type>(std::forward<Arguments>(Args)...);
        AddObject(Obj);
        
        return Obj;
    }

public:
    ObjectCollection();

    void AddObject(std::shared_ptr<Object> NewObject);
    void AddObject(std::vector<std::shared_ptr<Object>>& Objects);

    void Update(float DeltaTime);
    void LateUpdate(float DeltaTime);
    void Draw();

    void ProcessNewObjects();
    void ProcessRemovals();

private:
    std::vector<std::shared_ptr<Object>> Objects;
    std::vector<std::shared_ptr<Object>> NewObjects;

    std::unique_ptr<DrawableSystem> Drawables;
    std::unique_ptr<ColliderSystem> Collidables;
};
