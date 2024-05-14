#pragma once

enum class DrawLayer
{
    Default,
    Background,
    Foreground,
    Entities,
    UI,
};

class DrawableComponent
{
public:
    DrawableComponent();
    virtual ~DrawableComponent();

    virtual void Draw() = 0;

    void SetDrawLayer(DrawLayer NewLayer);
    DrawLayer GetDrawLayer() const;

    virtual bool ContinueToDraw() const = 0;

    void SetSortOrder(int NewSortOrder);
    int GetSortOrder() const;

private:
    int SortOrder;

    DrawLayer Layer;
};
