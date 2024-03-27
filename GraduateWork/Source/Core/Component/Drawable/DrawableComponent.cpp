#include "DrawableComponent.h"

DrawableComponent::DrawableComponent()
    : SortOrder(0)
{
}

DrawableComponent::~DrawableComponent()
{
}

void DrawableComponent::SetSortOrder(int NewSortOrder)
{
    SortOrder = NewSortOrder;
}

int DrawableComponent::GetSortOrder() const
{
    return SortOrder;
}
