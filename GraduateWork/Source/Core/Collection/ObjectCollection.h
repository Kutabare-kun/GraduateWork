#pragma once
#include <memory>
#include <vector>

#include "../System/Collider/ColliderSystem.h"
#include "../System/Drawable/DrawableSystem.h"

class GameModeBase;
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

    template <typename Type>
    std::shared_ptr<Type> GetObject()
    {
        static_assert(std::is_base_of_v<Object, Type>, "Type must derive from Object");

        for (auto& CurrentObject : Objects)
        {
            if (auto ThisObject = std::dynamic_pointer_cast<Type>(CurrentObject); ThisObject)
            {
                return ThisObject;
            }
        }

        for (auto& CurrentObject : NewObjects)
        {
            if (auto ThisObject = std::dynamic_pointer_cast<Type>(CurrentObject); ThisObject)
            {
                return ThisObject;
            }
        }

        return nullptr;
    }

public:
    ObjectCollection(DrawableSystem& Drawables, ColliderSystem& Collidables, GameModeBase& GameMode);

    void AddObject(std::shared_ptr<Object> NewObject);
    void AddObject(std::vector<std::shared_ptr<Object>>& Objects);

    void Update(float DeltaTime);
    void LateUpdate(float DeltaTime);
    void Draw(const Camera2D& OwnerCamera);

    void ProcessNewObjects();
    void ProcessRemovals();

private:
    std::vector<std::shared_ptr<Object>> Objects;
    std::vector<std::shared_ptr<Object>> NewObjects;

    DrawableSystem& Drawables;
    ColliderSystem& Collidables;
    GameModeBase& GameMode;
};
