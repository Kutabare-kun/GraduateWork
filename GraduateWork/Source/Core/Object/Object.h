#pragma once
#include <memory>
#include <vector>
#include <type_traits>

#include "../Component/Collider/ColliderComponent.h"
#include "../Component/Drawable/DrawableComponent.h"
#include "../Component/InstanceID/InstanceIDComponent.h"
#include "../Component/Transform/TransformComponent.h"
#include "../Context/SharedContext/SharedContext.h"
#include "../../Game/Components/Interactable/InteractableComponent.h"
#include "../../Game/Components/Interact/InteractComponent.h"

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

        if (auto ThisCollider = std::dynamic_pointer_cast<ColliderComponent>(NewComponent); ThisCollider)
        {
            Collidables.push_back(ThisCollider);
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
            if (auto Element = std::dynamic_pointer_cast<Type>(ExistingComponent); Element)
            {
                return Element;
            }
        }

        return nullptr;
    }

    template <typename Type>
    std::vector<std::shared_ptr<Type>> GetComponents()
    {
        std::vector<std::shared_ptr<Type>> MatchingComponents;
        for (auto& ExistingComponent : Components)
        {
            if (auto Element = std::dynamic_pointer_cast<Type>(ExistingComponent); Element)
            {
                MatchingComponents.emplace_back(Element);
            }
        }

        return MatchingComponents;
    }

public:
    explicit Object(SharedContext* Context, const Vector2& Position = {0.0f, 0.0f});

    virtual ~Object() = default;

    virtual void Awake();
    virtual void Start();

    virtual void Update(float DeltaTime);
    virtual void LateUpdate(float DeltaTime);

    virtual void Draw();

    void OnCollisionBeginOverlap(std::shared_ptr<ColliderComponent> Other);
    void OnCollisionStayOverlap(std::shared_ptr<ColliderComponent> Other);
    void OnCollisionEndOverlap(std::shared_ptr<ColliderComponent> Other);

    bool IsQueuedForRemoval();
    void QueueForRemoval();

    std::shared_ptr<DrawableComponent> GetDrawable() const { return DrawableComp; }
    std::shared_ptr<TransformComponent> GetTransform() const { return TransformComp; }
    std::shared_ptr<InstanceIDComponent> GetInstanceID() const { return InstanceIDComp; }

    SharedContext* GetContext() const { return Context; }
    std::string GetName() const { return Name + std::to_string(InstanceIDComp->GetID()); }

    void SetName(const std::string& NewName) { Name = NewName; }

protected:
    bool bQueuedForRemoval;

    SharedContext* Context;

    std::shared_ptr<TransformComponent> TransformComp;
    std::shared_ptr<DrawableComponent> DrawableComp;
    std::shared_ptr<InstanceIDComponent> InstanceIDComp;

    std::vector<std::shared_ptr<ActorComponent>> Components;
    std::vector<std::shared_ptr<ColliderComponent>> Collidables;

    std::string Name;
};
