#pragma once
#include <memory>

#include "../ActorComponent.h"

enum class Tag
{
    Default,
    Player,
    NPC,
    Enemy,
};

class TagComponent
    : public ActorComponent
{
public:
    TagComponent(Object* Owner);

    Tag Get() const {return TagValue;}
    void Set(Tag NewTag) {TagValue = NewTag;}

    bool Compare(std::shared_ptr<TagComponent> Other) const;
    bool Compare(Tag Other) const;

private:
    Tag TagValue;
};
