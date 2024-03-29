#include "DrawableComponent.h"

DrawableComponent::DrawableComponent()
    : SortOrder(0), Layer(DrawLayer::Default)
{
}

DrawableComponent::~DrawableComponent()
{
}

void DrawableComponent::SetDrawLayer(DrawLayer NewLayer)
{
    Layer = NewLayer;
}

DrawLayer DrawableComponent::GetDrawLayer() const
{
    return Layer;
}

void DrawableComponent::SetSortOrder(int NewSortOrder)
{
    SortOrder = NewSortOrder;
}

int DrawableComponent::GetSortOrder() const
{
    return SortOrder;
}
