#pragma once
#include <memory>

#include "../ActorComponent.h"

enum class Tag
{
    Default,
    Player,
    NPC,
    Enemy,
    Ability,
    PowerUp,
};

template <typename TypeTag = Tag>
class TagComponent
    : public ActorComponent
{
public:
    TagComponent(Object* Owner)
        : ActorComponent(Owner)
    {
        TagValue = static_cast<TypeTag>(0);
    }

    TypeTag Get() const { return TagValue; }
    void Set(TypeTag NewTag) { TagValue = NewTag; }

    bool Compare(std::shared_ptr<TagComponent<TypeTag>> Other) const
    {
        return Other->Get() == TagValue;
    }

    bool Compare(TypeTag Other) const
    {
        return Other == TagValue;
    }

private:
    TypeTag TagValue;
};
