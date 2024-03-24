#pragma once
#include <memory>
#include <vector>

#include "../Component/ActorComponent.h"

class Object
{
public:
    template <typename Type, typename... Arguments>
    std::shared_ptr<Type> AddComponent(Arguments&&... Args) // 1
    {
        // This ensures that we only try to add a class the derives 
        // from Component. This is tested at compile time.
        static_assert(std::is_base_of<ActorComponent, Type>::value, "T must derive from Component");

        // Check that we don't already have a component of this type.
        auto Component = GetComponent<Type>();
        if (Component) return Component;

        // The object does not have this component so we create it and 
        // add it to our list.
        std::shared_ptr<Type> NewComponent = std::make_shared<Type>(std::forward<Arguments>(Args)...);
        Components.push_back(NewComponent);

        return NewComponent;
    }

    template <typename Type>
    std::shared_ptr<Type> GetComponent()
    {
        static_assert(std::is_base_of<ActorComponent, Type>::value, "T must derive from Component");

        // Check that we don't already have a component of this type.
        for (auto& ExisitingComponent : Components)
        {
            if (std::dynamic_pointer_cast<Type>(ExisitingComponent))
            {
                return std::dynamic_pointer_cast<Type>(ExisitingComponent);
            }
        }

        return nullptr;
    }

public:
    virtual ~Object() = default;
    
    virtual void EventTick(float DeltaTime) = 0;

    // Return true if actor can tick
    bool IsEnableTicks() const { return bEnableTicks; }

    std::vector<std::shared_ptr<ActorComponent>>& GetAllComponents() { return Components; }

protected:
    bool bEnableTicks = true;

private:
    std::vector<std::shared_ptr<ActorComponent>> Components;
};
