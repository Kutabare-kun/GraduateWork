#include "TagComponent.h"

TagComponent::TagComponent(Object* Owner)
    : ActorComponent(Owner), TagValue(Tag::Default)
{
}

bool TagComponent::Compare(std::shared_ptr<TagComponent> Other) const
{
    return Other->Get() == TagValue;
}

bool TagComponent::Compare(Tag Other) const
{
    return Other == TagValue;
}
