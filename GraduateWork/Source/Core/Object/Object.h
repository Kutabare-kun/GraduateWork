#pragma once
#include <memory>
#include <vector>
#include <type_traits>

#include "../Component/Drawable/DrawableComponent.h"
#include "../Component/InstanceID/InstanceIDComponent.h"
#include "../Component/Transform/TransformComponent.h"

class Object
{
public:
    template <typename Type, typename... Arguments>
    std::shared_ptr<Type> AddComponent(Arguments&&... Args) // 1
    {
        // This ensures that we only try to add a class the derives 
        // from Component. This is tested at compile time.
        static_assert(std::is_base_of<ActorComponent, Type>::value, "Type must derive from Component");

        // Check that we don't already have a component of this type.
        if (auto Component = GetComponent<Type>(); Component)
            return Component;

        // The object does not have this component so we create it and 
        // add it to our list.
        std::shared_ptr<Type> NewComponent = std::make_shared<Type>(std::forward<Arguments>(Args)...);
        Components.push_back(NewComponent);

        if (auto ThisDrawable = std::dynamic_pointer_cast<DrawableComponent>(NewComponent); ThisDrawable)
        {
            DrawableComp = ThisDrawable;
        }

        return NewComponent;
    }

    template <typename Type>
    std::shared_ptr<Type> GetComponent() const
    {
        static_assert(std::is_base_of<ActorComponent, Type>::value, "Type must derive from Component");

        // Check that we don't already have a component of this type.
        for (auto& ExistingComponent : Components)
        {
            if (std::dynamic_pointer_cast<Type>(ExistingComponent))
            {
                return std::dynamic_pointer_cast<Type>(ExistingComponent);
            }
        }

        return nullptr;
    }

public:
    explicit Object(const Vector2& Position = { 0.0f, 0.0f })
    {
        TransformComp = AddComponent<TransformComponent>(this, Position);
        InstanceIDComp = AddComponent<InstanceIDComponent>(this);
    }
    
    virtual ~Object() = default;

    virtual void Awake()
    {
        for (auto& Component : Components)
        {
            Component->Awake();
        }
    }

    virtual void Start()
    {
        for (auto& Component : Components)
        {
            Component->Start();
        }
    }
    
    virtual void Update(float DeltaTime)
    {
        for (auto& Component : Components)
        {
            Component->Update(DeltaTime);
        }
    }

    virtual void LateUpdate(float DeltaTime)
    {
        for (auto& Component : Components)
        {
            Component->LateUpdate(DeltaTime);
        }
    }

    virtual void Draw()
    {
        DrawableComp->Draw();
    }

    bool IsQueuedForRemoval()
    {
        return bQueuedForRemoval;
    }
    
    void QueueForRemoval()
    {
        bQueuedForRemoval = true;
    }

    std::shared_ptr<DrawableComponent> GetDrawable()
    {
        return DrawableComp;
    }

    std::shared_ptr<TransformComponent> GetTransform()
    {
        return TransformComp;
    }

    std::shared_ptr<InstanceIDComponent> GetInstanceID()
    {
        return InstanceIDComp;
    }

protected:
    bool bQueuedForRemoval = false;
    std::shared_ptr<TransformComponent> TransformComp;
    std::shared_ptr<DrawableComponent> DrawableComp;
    std::shared_ptr<InstanceIDComponent> InstanceIDComp;
    
    std::vector<std::shared_ptr<ActorComponent>> Components;
};
