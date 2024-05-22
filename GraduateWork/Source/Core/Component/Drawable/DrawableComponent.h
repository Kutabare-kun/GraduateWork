#pragma once

#include <raylib.h>

enum class DrawLayer
{
    Default,
    Background,
    PowerUp,
    Entities,
    Foreground,
    UI,
};

class DrawableComponent
{
public:
    DrawableComponent();
    virtual ~DrawableComponent();

    virtual void Draw(const Camera2D& OwnerCamera) = 0;

    void SetDrawLayer(DrawLayer NewLayer);
    DrawLayer GetDrawLayer() const;

    virtual bool ContinueToDraw() const = 0;

    void SetSortOrder(int NewSortOrder);
    int GetSortOrder() const;

private:
    int SortOrder;

    DrawLayer Layer;
};
